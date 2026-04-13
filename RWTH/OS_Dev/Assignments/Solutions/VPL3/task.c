#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int tee(const char *output_file) {
	int ret = 0;
	char buffer[BUFFER_SIZE];
	int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	ssize_t read_size;
	while ((read_size = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
		if (write(fd, buffer, read_size) <= 0) {
			perror("write fd");
			ret = -1;
			goto out;
		}
		if (write(STDOUT_FILENO, buffer, read_size) <= 0) {
			perror("write stdout");
			ret = -1;
			goto out;
		}
	}
	if (read_size < 0) {
		perror("read");
	}

out:
	close(fd);
	return ret;
}

int reverse_buffer(char *buffer, size_t size)
{
	char inverted[BUFFER_SIZE];
	for (size_t i = 0; i < size; i++) {
		inverted[i] = buffer[size - 1 - i];
	}
	memcpy(buffer, inverted, size);
	return 0;
}

int reverse_file_simple(const char *input_file, const char *output_file) {
	int input = open(input_file, O_RDONLY);
	char buf;
	ssize_t size_read;
	if (input < 0) {
		perror("open");
		return -1;
	}
	int output = open(output_file, O_CREAT | O_WRONLY, 0600);
	if (output < 0) {
		perror("open");
		close(input);
		return -1;
	}

	lseek(input, -1, SEEK_END);

	do {
		if ((size_read = read(input, &buf, 1)) < 0) {
			perror("read");
			break;
		}
		if (write(output, &buf, 1) < 0) {
			perror("write");
			break;
		}
	} while((lseek(input , -2, SEEK_CUR)) > -1);

	close(input);
	close(output);
	return 0;
}

int reverse_file(const char *input_file, const char *output_file) {
	char buf[BUFFER_SIZE] = {0};
	off_t current_offset;
	ssize_t size_read = 0;
	ssize_t read_size = 0;
	int input = open(input_file, O_RDONLY);

	if (input < 0) {
		perror("open");
		return -1;
	}
	int output = open(output_file, O_CREAT | O_TRUNC | O_WRONLY, 00600);
	if (output < 0) {
		perror("open");
		close(input);
		return -1;
	}

	current_offset = lseek(input , 0 , SEEK_END);

	while(current_offset > 0) {
		read_size = current_offset < BUFFER_SIZE ? current_offset : BUFFER_SIZE;
		current_offset -= read_size;
		lseek(input , current_offset, SEEK_SET);

		size_read = read(input, buf, read_size);

		if (size_read < 0 || read_size != size_read) {
			perror("read");
			return -1;
		}

		reverse_buffer(buf, size_read);

		if (write(output, &buf, size_read) < 0) {
			perror("write");
			return -1;
		}
	}

	close(input);
	close(output);
	return 0;
}
