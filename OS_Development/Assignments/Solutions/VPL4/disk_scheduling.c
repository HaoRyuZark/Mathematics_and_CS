#include <fcntl.h>
#include <unistd.h>
#include "tasks_lib.h"
#include <stdbool.h>

#ifdef VPL
#include "tasks.h"
#endif


#define ABS(x) ((x) > 0 ? (x) : (-(x)))
#define DST(x,y) ABS((x) - (y))

// First Come First Served
int FCFS(struct device_t* device, int requests[], int size) {
	int seek_time = 0;

	for (int *c = requests; c < requests + size; c++) {
		seek_time += DST(dev_get_cylinder(device), *c);
		dev_move_to_cylinder(device, *c);
		dev_work(device);
	}

	return seek_time;
}

// find the next request to process based on the current cylinder position
int ssf_find_next(int array[], int size, int arm_pos, enum direction direction) {
	int *candidate = &array[0];
	int request_pos = 0;

	for (int *elem = &array[0]; elem < array + size; elem++) {

		if (*candidate == -1) {
			candidate = elem;
		}
		else if (*elem != -1) {
			bool nearest = ((DST(arm_pos, *elem) < DST(arm_pos, *candidate)));
			bool equal_left = (DST(arm_pos, *elem) == DST(arm_pos, *candidate) && direction == RIGHT && *candidate < *elem);
			bool equal_right = (DST(arm_pos, *elem) == DST(arm_pos, *candidate) && direction == LEFT && *candidate > *elem);
			if (nearest || equal_left || equal_right) {
				candidate = elem;
			}
		}

	}

	int tmp = *candidate;
	*candidate = -1; // mark it done
	return tmp;
}

inline void update_direction(struct device_t* device, int old_c, int new_c) {
	enum direction dir = dev_get_direction(device);
	if ((dir == RIGHT && (new_c < old_c)) || (dir == LEFT && (new_c > old_c)))
		dev_switch_direction(device);
}

// Shortest Seek First
int SSF(struct device_t* device, int requests[], int size) {
	int cylinder = dev_get_cylinder(device);
	int old_cylinder;
	int seek_time = 0;
	int total = size;

	while (total > 0) {
		old_cylinder = cylinder;
		cylinder = ssf_find_next(requests, size, cylinder, dev_get_direction(device));
		seek_time += DST(dev_get_cylinder(device), cylinder);
		dev_move_to_cylinder(device, cylinder);
		dev_work(device);
		update_direction(device, old_cylinder, cylinder);
		total--;
	}

	return seek_time;
}

// remove the first element equal to value in the array
// return true only if found
static bool remove_element(int array[], int size, int value) {
	for (int *c = array; c < array + size; c++) {
		if (*c == value) {
			*c = -1;
			return true;
		}
	}
	return false;
}

void scan_update_direction(struct device_t* device) {
	enum direction dir = dev_get_direction(device);
	if ((dir == LEFT && dev_get_cylinder(device) == 0) || (dir == RIGHT && dev_get_cylinder(device) == dev_get_max_cylinder(device))) {
		dev_switch_direction(device);
	}
}

int SCAN(struct device_t* device, int requests[], int size) {
	int total = size;
	int seek_time = 0;
	int max_cylinder = dev_get_max_cylinder(device);
	int next_cylinder;
	while (total > 0) {
		while (remove_element(requests, size, dev_get_cylinder(device))) {
			dev_work(device);
			total--;
		}
		if (total > 0) {
			scan_update_direction(device);
			next_cylinder = dev_get_direction(device) == RIGHT ? dev_get_cylinder(device) + 1 : dev_get_cylinder(device) - 1;
			dev_move_to_cylinder(device, next_cylinder);
			seek_time += 1;
		}
	}
	return seek_time;
}
