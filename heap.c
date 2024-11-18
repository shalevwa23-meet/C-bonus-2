#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#include "heap.h"
#include "tests.h"

unsigned char heap[HEAP_SIZE];
unsigned char heap_status[HEAP_SIZE];

// Helper function to find the best subheap to fit the requested size
void find_best_subheap(size_t size, int *start, int *length) {
    int best_start = -1;
    //initialised to unexisting index

    int best_length = HEAP_SIZE + 1;
    //initialised to more than max_length

    int current_start = -1;
    int current_length = 0;

    for (int i = 0; i < HEAP_SIZE; ++i) {
        if (heap_status[i] == 0 && i < HEAP_SIZE-1) // Free space && not end
        { 
            if (current_start == -1)
            {
                current_start = i;
            }
            current_length++;
        }
        else // Allocated space
        { 
            if (current_start != -1
                && current_length >= size
                && current_length < best_length)
            {
                best_start = current_start;
                best_length = current_length;
            }
            current_start = -1;
            current_length = 0;
        }
    }
    *start = best_start;
    *length = best_length;
    return;
}

// Helper function to calculate the distances and find the better edge
int find_best_edge(int start, int length, size_t size) {
    // Calculate leftward distance
    int left_dist = 0;
    for (int i = start - 1; i >= 0; --i) {
        if (heap_status[i] == 0) {
            break;
        }
        left_dist++;
    }

    // Calculate rightward distance
    int right_dist = 0;
    for (int i = start + length; i < HEAP_SIZE; ++i) {
        if (heap_status[i] == 0) {
            break;
        }
        right_dist++;
    }
    // Compare distances and choose the edge
    if (right_dist < left_dist)
    {
        return start + length - size; // Allocate from right edge
    }

    return start; // Allocate from left edge
}

// Mark allocation of SIZE bytes from ALLOCATION_START
// On the heap_status array.
void mark_allocation(int allocation_start, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        heap_status[allocation_start + i] = size - i;
    }
    return;
}

// Allocate memory
void *my_malloc(size_t size) {
    if (size == 0 || size > HEAP_SIZE) {
        return NULL;
    }

    int subheap_start = -1;
    int subheap_length = HEAP_SIZE+1;
    find_best_subheap(size, &subheap_start, &subheap_length);
    if (subheap_start == -1)
    {
        return NULL; // No suitable subheap found
    }

    int allocation_start = find_best_edge(subheap_start, subheap_length, size);

    mark_allocation(allocation_start, size);

    return heap + allocation_start;
}

// Allocate and zero-initialize memory
void *my_calloc(size_t num, size_t size) {
    size_t total_size = num * size;
    void *ptr = my_malloc(total_size);
    if (ptr) {
        memset(ptr, 0, total_size);
    }
    return ptr;
}

// Reallocate memory
void *my_realloc(void *ptr, size_t size) {
    if (ptr == NULL) {
        // Behave like malloc for NULL input
        return my_malloc(size);
    }

    // Calculate the block's starting index in the heap
    size_t block_start = (unsigned char *)ptr - heap;

    // Retrieve the current size of the block
    size_t current_size = heap_status[block_start];

    if (current_size > size)
    {
        // Case 1: Shrink the block if the new size is smaller

        my_free(ptr+size); // Free everything after the needed size
        mark_allocation(block_start, size);
        return ptr;
    }
    else
    {
        // Case 2: Try to expand in place
        size_t next_block_start = block_start + current_size;
        size_t free_space = 0;

        // Count the contiguous free space after the current block
        while (next_block_start + free_space < HEAP_SIZE
                && heap_status[next_block_start + free_space] == 0)
        {
            free_space++;
        }

        if (current_size + free_space >= size)
        {
            // Enough free space to expand in place
            mark_allocation(block_start, size);
            return ptr;
        }
        else
        {
            // Case 3: Allocate a new block and copy data
            void *new_block = my_malloc(size);
            if (new_block == NULL) {
                return NULL; // Allocation failed
            }
            // Copy data to the new block
            memcpy(new_block, ptr, current_size);
            // Free the old block
            my_free(ptr);
            return new_block;
        }
    }
}


// Free memory
void my_free(void *ptr) {
    if (!ptr) {
        return;
    }

    unsigned char *start = (unsigned char *)ptr;
    int index = start - heap;
    int size = heap_status[index];

    for(int i = 0; i<size; i++)
    {
        heap_status[index+i] = 0;
    }
}

// Debug function to display heap status
void print_heap_status() {
    printf("Heap status:\n");
    for (int i = 0; i < HEAP_SIZE; ++i) {
        printf("%d ", heap_status[i]);
    }
    printf("\n");
}

int main() {
    run_all_tests();
    return 0;
}