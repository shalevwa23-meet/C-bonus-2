#ifndef TESTS_H
#define TESTS_H

#include <stdio.h> // For printf
#include "heap.h"  // Include the heap implementation

/**
 * @brief Runs all tests for the heap allocator.
 * 
 * Each test function validates a specific scenario of heap behavior.
 * Errors or unexpected results in any test will be reported.
 */
void run_all_tests(void);

/**
 * @brief Tests basic allocation and freeing.
 * @return 0 if the test passes, 1 otherwise.
 */
int test_basic_allocation();

/**
 * @brief Tests memory exhaustion when requesting more than available.
 * @return 0 if the test passes, 1 otherwise.
 */
int test_memory_exhaustion();

/**
 * @brief Tests `realloc` shrinking a block.
 * @return 0 if the test passes, 1 otherwise.
 */
int test_realloc_shrink();

/**
 * @brief Tests `realloc` expanding in place.
 * @return 0 if the test passes, 1 otherwise.
 */
int test_realloc_expand();

/**
 * @brief Tests `realloc` when expansion requires moving the block.
 * @return 0 if the test passes, 1 otherwise.
 */
int test_realloc_move();

/**
 * @brief Tests freeing a block and reallocating in its space.
 * @return 0 if the test passes, 1 otherwise.
 */
int test_free_and_reallocate();

/**
 * @brief Tests freeing null pointers and invalid frees.
 * @return 0 if the test passes, 1 otherwise.
 */
int test_invalid_free();

#endif // TESTS_H
