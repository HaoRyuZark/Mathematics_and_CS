#include "buffer_ring.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

struct BufferRing *init_buffer_ring(int size) {
	int ret;

	struct BufferRing *ring =
		mmap(NULL, sizeof(struct BufferRing), PROT_READ | PROT_WRITE,
	         MAP_SHARED | MAP_ANON, -1, 0);

	if (!ring) {
		perror("mmap");
		goto error;
	}

	ring->buffer = mmap(NULL, size * sizeof(int), PROT_READ | PROT_WRITE,
	                  MAP_SHARED | MAP_ANON, -1, 0);

	if (!ring->buffer) {
		perror("mmap");
		munmap(ring, sizeof(struct BufferRing));
		goto error;
	}


	ret = sem_init(&ring->free_space, 1, size);
	if (ret) {
		perror("sem_init");
		goto unmap;
	}
	ret = sem_init(&ring->used_space, 1, size);
	if (ret) {
		perror("sem_init");
		sem_destroy(&ring->free_space);
		goto unmap;
	}
	ret = sem_init(&ring->mutex, 1, 1);
	if (ret) {
		perror("sem_init");
		sem_destroy(&ring->free_space);
		sem_destroy(&ring->used_space);
		goto unmap;
	}

	ring->size = size;
	ring->idx_reader = 0;
	ring->idx_writer = 0;

	return ring;
unmap:
	munmap(ring->buffer, size * sizeof(int));
	munmap(ring, sizeof(struct BufferRing));
error:
	return NULL;
}

void free_buffer_ring(struct BufferRing *br) {
	sem_destroy(&br->free_space);
	sem_destroy(&br->used_space);
	sem_destroy(&br->mutex);
	munmap(br->buffer, br->size * sizeof(int));
	munmap(br, sizeof(struct BufferRing));
	return;
}

int buffer_ring_read(struct BufferRing *br) {
	if (!br)
		return -1;

	int value;

	sem_wait(&br->used_space);
	sem_wait(&br->mutex);

	value = br->buffer[br->idx_reader];
	br->idx_reader = (br->idx_reader + 1) % br->size;

	sem_post(&br->mutex);
	sem_post(&br->free_space);

	return value;
}

void buffer_ring_write(struct BufferRing *br, int value) {
	if (!br)
		return;

	sem_wait(&br->free_space);
	sem_wait(&br->mutex);

	br->buffer[br->idx_writer] = value;
	br->idx_writer = (br->idx_writer + 1) % br->size;

	sem_post(&br->mutex);
	sem_post(&br->used_space);
}
