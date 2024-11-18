#include "tests.h"

void run_all_tests() {
    printf("Running tests...\n");

    int failed = 0;
    failed += test_basic_allocation();
    failed += test_memory_exhaustion();
    failed += test_realloc_shrink();
    failed += test_realloc_expand();
    failed += test_realloc_move();
    failed += test_free_and_reallocate();
    failed += test_invalid_free();

    if (failed == 0) {
        printf("All tests passed!\n");
    } else {
        printf("%d test(s) failed.\n", failed);
    }
}

int test_basic_allocation() {
    printf("Test: Basic allocation and free\n");

    void *p1 = my_malloc(10);
    void *p2 = my_malloc(20);
    if (!p1 || !p2) return 1;

    my_free(p1);
    my_free(p2);

    // Verify that the entire heap is free
    for (int i = 0; i < HEAP_SIZE; i++) {
        if (heap_status[i] != 0) return 1;
    }

    return 0;
}

int test_memory_exhaustion() {
    printf("Test: Memory exhaustion\n");

    void *p = my_malloc(HEAP_SIZE + 1);
    if (p != NULL) return 1; // Should fail to allocate

    return 0;
}

int test_realloc_shrink() {
    printf("Test: Realloc shrink\n");

    void *p = my_malloc(20);
    if (!p) return 1;

    p = my_realloc(p, 10);
    if (!p) return 1;

    // Verify that extra space is freed
    for (int i = 10; i < 20; i++) {
        if (heap_status[i] != 0) return 1;
    }

    my_free(p);
    return 0;
}

int test_realloc_expand() {
    printf("Test: Realloc expand\n");

    void *p = my_malloc(10);
    if (!p) return 1;

    p = my_realloc(p, 20);
    if (!p) return 1;

    // Verify the block size
    if (heap_status[0] != 20) return 1;

    my_free(p);
    return 0;
}

int test_realloc_move() {
    printf("Test: Realloc move\n");

    void *p1 = my_malloc(20);
    void *p2 = my_malloc(50);
    void *p3 = my_malloc(1);
    if (!p1 || !p2) return 1;

    // Force move by reallocating p1 to a larger size
    p1 = my_realloc(p1, 21);
    if (!p1) return 1;

    // Verify p1 moved and is 21 bytes long
    if (heap_status[21] != 21) return 1;

    my_free(p1);
    my_free(p2);
    my_free(p3);
    return 0;
}

int test_free_and_reallocate() {
    printf("Test: Free and reallocate\n");

    void *p1 = my_malloc(20);
    if (!p1) return 1;

    my_free(p1);

    void *p2 = my_malloc(20);
    if (!p2) return 1;

    // Ensure the reallocated block starts at the same position
    if (p1 != p2) return 1;

    my_free(p2);
    return 0;
}

int test_invalid_free() {
    printf("Test: Invalid free\n");

    my_free(NULL); // Should do nothing
    void *invalid_ptr = (void *)(heap + HEAP_SIZE + 1);
    my_free(invalid_ptr); // Should do nothing

    // Ensure no corruption occurred
    for (int i = 0; i < HEAP_SIZE; i++) {
        if (heap_status[i] != 0) return 1;
    }

    return 0;
}