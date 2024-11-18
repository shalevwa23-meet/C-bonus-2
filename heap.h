#ifndef HEAP_H
#define HEAP_H

#include <stddef.h> // For size_t

/** 
 * @brief Simulates a memory heap for dynamic allocation.
 * The heap is implemented as a global array of fixed size (HEAP_SIZE),
 * along with a status array to track allocated and free memory blocks.
 */

#define HEAP_SIZE 128

extern unsigned char heap[HEAP_SIZE];
extern unsigned char heap_status[HEAP_SIZE];

/** 
 * @brief Allocates a block of memory of the specified size.
 * 
 * @param size The size of the memory block to allocate (in bytes).
 * @return A pointer to the allocated memory block, or NULL if the allocation fails.
 * 
 * This function finds the smallest contiguous block of free memory (subheap)
 * that can fit the requested size, calculates the best edge for allocation,
 * and marks the corresponding region in the heap status array as allocated.
 */
void *my_malloc(size_t size);

/** 
 * @brief Allocates memory for an array and initializes it to zero.
 * 
 * @param num The number of elements in the array.
 * @param size The size of each element (in bytes).
 * @return A pointer to the allocated memory block, or NULL if the allocation fails.
 * 
 * This function combines allocation and initialization. It finds a suitable
 * block of memory for `num * size` bytes and initializes all bytes to 0.
 */
void *my_calloc(size_t num, size_t size);

/** 
 * @brief Changes the size of an allocated memory block.
 * 
 * @param ptr A pointer to the previously allocated memory block.
 * @param size The new size of the memory block (in bytes).
 * @return A pointer to the reallocated memory block, or NULL if the operation fails.
 * 
 * This function attempts to resize the memory block pointed to by `ptr`. If the
 * new size is larger, a new block may be allocated, and data from the old block
 * is copied. If the new size is smaller, excess memory is freed.
 */
void *my_realloc(void *ptr, size_t size);

/** 
 * @brief Frees a previously allocated memory block.
 * 
 * @param ptr A pointer to the memory block to free.
 * 
 * This function marks the memory block pointed to by `ptr` as free in the heap
 * status array. If `ptr` is NULL or the block has already been freed, the function
 * does nothing.
 */
void my_free(void *ptr);

/**
 * @brief Prints the current status of the heap.
 * 
 * This function outputs the state of the heap status array, showing which
 * blocks are allocated, free, or part of larger allocations.
 * 
 * This is primarily used for debugging purposes.
 */
void print_heap_status(void);

#endif // HEAP_H
