#pragma once
#include <stdlib.h>


typedef struct repo_item repo_t;
struct repo_item
{
    repo_t* next; 
};


void* memory_static_alloc(size_t size);
size_t memory_info(void);
void memory_heap_setup(void *block, size_t size);

#define DEPLOY_PROCEDURE_init_heap(SIZE)                    \
{                                                           \
    static char memory_block[SIZE];                         \
    memory_heap_setup(memory_block, sizeof(memory_block));  \
}

