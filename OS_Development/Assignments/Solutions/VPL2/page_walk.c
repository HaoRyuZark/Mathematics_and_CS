#include "page_walk.h"

// Jérôme Coquisart
// coquisart@os.rwth-aachen.de

// Define the number of levels in the page table
#define LEVEL_NUMBER 4

// A bitmask that can be used to extract the level index from a page table entry.
#define LEVEL_INDEX_BIT_MASK ((1 << 9) - 1)

// The size of a page in bytes.
#define PAGE_SIZE (1 << OFFSET_BITS)

// A bitmask that can be used to extract the page offset from a virtual address.
#define PAGE_SIZE_MASK (PAGE_SIZE - 1)

// A macro that extracts the page offset from a virtual address.
#define PAGE_OFFSET(va) ((va) & (PAGE_SIZE_MASK))

// A bitmask that can be used to extract the physical address from a page table entry.
#define PHYSICAL_ADDR_MASK ((1UL << 52) - 1) & ~PAGE_SIZE_MASK

/**
 * \brief Sets the nth bit (flag) to 1 in a 64-bit integer.
 *
 * \param value The 64-bit integer to modify.
 * \param flag The bit position to set (0-63).
 *
 * \returns The modified 64-bit integer with the nth bit set to 1.
 */
uint64_t set_bit(uint64_t value, unsigned int flag){
	return value | (1UL << flag);
}

/**
 * \brief Tests the nth (flag) bit in a 64-bit integer.
 *
 * \param value The 64-bit integer to test.
 * \param flag The bit position to test (0-63).
 *
 * \returns true if the nth bit is set to 1, false otherwise.
 */
bool test_bit(uint64_t value, unsigned int flag){
	return value & (1UL << flag);
}

/**
 * \brief Clears the nth (flag)  bit in a 64-bit integer.
 *
 * \param value The 64-bit integer to modify.
 * \param flag The bit position to clear (0-63).
 *
 * \returns The modified 64-bit integer with the nth bit cleared.
 */
uint64_t clear_bit(uint64_t value, unsigned int flag){
	return value & ~(1UL << flag);
}

/**
 * Calculates the offset of the given level page table
 *
 * @param virtual_address: the virtual address associated
 * @param level: the level of the page table that we wan't the offset
 *
 * @return the offset of the given level page table
 */
uint64_t page_table_index(uint64_t virtual_address, int level) {
	int shift = OFFSET_BITS + (LEVEL_NUMBER - level) * LEVEL_INDEX_BITS;
	return (virtual_address >> shift) & LEVEL_INDEX_BIT_MASK;
}

/**
 * \brief Calculates the offset of the levels in the  page table
 *
 * @param virtual_address: virtual address associated
 *
 * @return offset of the levels in the page table
 */
uint64_t index_page_level_1(uint64_t virtual_address){
	return page_table_index(virtual_address, 1);
}
uint64_t index_page_level_2(uint64_t virtual_address){
	return page_table_index(virtual_address, 2);
}
uint64_t index_page_level_3(uint64_t virtual_address){
	return page_table_index(virtual_address, 3);
}
uint64_t index_page_level_4(uint64_t virtual_address){
	return page_table_index(virtual_address, 4);
}

/**
 * \brief Converts a PTE to physical address
 *
 * @param pte: page table entry
 * @param virtual_address:  virtual address associated with the PTE
 *
 * @return the physical address
 */
uint64_t pte_to_physical(uint64_t pte, uint64_t virtual_address){
	uint64_t page_frame = pte & PHYSICAL_ADDR_MASK;
	uint64_t physical_address = page_frame | PAGE_OFFSET(virtual_address);
	return physical_address;
}

uint64_t *va_to_pte(uint64_t *page_table_pointer, uint64_t virtual_address) {
  if (!page_table_pointer)
    return NULL;

  //Find out the PTE associated with the virtual address
  for (int level = 1; level < LEVEL_NUMBER; level++) {
    uint64_t offset = page_table_index(virtual_address, level);
    page_table_pointer = (uint64_t *)page_table_pointer[offset];
    if (!page_table_pointer)
      return NULL;
  }

  // PTE
  uint64_t offset = page_table_index(virtual_address, LEVEL_NUMBER);
  uint64_t *pte = &page_table_pointer[offset];
  return pte;
}

/**
 * \brief Performs a page walk for translation and checks for page faults and permission errors
 *
 * @param page_table_pointer: pointer to the page table
 * @param virtual_address:  virtual address to be translated
 * @param mode: user or supervisor mode
 * @param operation: read or write
 *
 * @return the physical address corresponding to the virtual address, or 0 if a fault is triggered
 */
uint64_t page_walk(uint64_t *page_table_pointer, uint64_t virtual_address, enum mode mode, enum operation operation){
  uint64_t* p_pte = va_to_pte(page_table_pointer, virtual_address);
  if (!p_pte) {
    segmentation_fault();
    return 0;
  }
  uint64_t pte = *p_pte;

  //Checks if there is a permission error
  if (((operation == WRITE) && !(test_bit(pte, READWRITE))) || ((mode == USER) && !(test_bit(pte, USERSUPERVISOR)))) {
    segmentation_fault();
    return 0;
  }
    //Checks if the associated page frame is not present in memory
  if (!test_bit(pte, PRESENT)) {
	page_fault();
    return 0;
  }
  //If no fault is triggered, return the physical address
  return pte_to_physical(pte, virtual_address);
}
