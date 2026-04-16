#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef VPL
// Don't touch these lines
#include "interrupt.h"
extern uint8_t** reg_buffer_device;
#else
/*
  These definitions are here in case you want to develop locally.
    - They are NOT completely equivalent to the functions that will
      be used on VPL for grading.
    - Any changes you make to them will NOT be considered in VPL
      while grading.
*/

// Size of the device buffer
#define SIZE 4096

// Pointer to the register that holds the address of the device buffer.
uint8_t** reg_buffer_device;

// Enables interrupts
void enable_interrupts() { printf("interrupts enabled.\n"); }

// Disables interrupts
void disable_interrupts() { printf("interrupts disabled.\n"); }

// Signals that the register has been copied
void ack_reg_copied() { printf("ack_reg_copied\n"); }

// Signals that the buffer has been copied
void ack_buffer_copied() { printf("ack_buf_copied\n"); }

// Copies src to dest
void copy_dev_buffer(uint8_t* src, uint8_t* dest, size_t size) {
  memcpy(dest, src, size);
}

// cleans up the buffer used in schedule_upper_half (e.g. deallocate, etc.)
// implement this below!
void schedule_upper_half_post_hook(void* ptr);

void schedule_upper_half(uint8_t* buffer) {
  // does something interesting with the buffer
  // ...
  // cleans up afterwards
  schedule_upper_half_post_hook(buffer);
}

#endif

// ----- Start implementing things here ----- //
// uint8_t buffer[SIZE];

int ISR() {
  disable_interrupts();
  uint8_t* dev_buffer = *reg_buffer_device;
  ack_reg_copied();
  enable_interrupts();

  uint8_t *buffer = malloc(sizeof(uint8_t) * SIZE);
  copy_dev_buffer(dev_buffer, buffer, SIZE);

  ack_buffer_copied();

  schedule_upper_half(buffer);
  return 0;
}

// Cleans up the buffer used in schedule_upper_half (e.g. deallocate, etc.)
// Do NOT call this function yourself. Assume it is called automatically in
// schedule_upper_half.
void schedule_upper_half_post_hook(void* ptr) {
	free(ptr);
}

// For testing, you can get a device buffer like this:
// Remember to NOT include a main() function in your submission
// (Inside ifndef VPL, it's ok)
#ifndef VPL
int main() {
  uint8_t dev_buf[SIZE] = {0xab};
  uint8_t* dev_buf_ptr = (uint8_t*)dev_buf;
  reg_buffer_device = &dev_buf_ptr;
  ISR();
}
#endif
