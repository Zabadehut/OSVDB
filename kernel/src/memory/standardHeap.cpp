#include "standardHeap.h"

uintptr_t current_break;

void *sbrk(intptr_t incr)
{
    uintptr_t old_break = current_break;
    current_break += incr;
    return (void*) old_break;
}

void mergeContiguousBlocks(free_block* block) {
    while(block && block->next) {
        if ((char*)block + sizeof(free_block) + block->size == (char*)block->next) {
            block->size += sizeof(free_block) + block->next->size;
            block->next = block->next->next;
        }
        block = block->next;
    }
}


void* standardMalloc(size_t size) {
    size = (size + sizeof(size_t) + (align_to - 1)) & ~ (align_to - 1);
    free_block* block = free_block_list_head.next;
    free_block** head = &(free_block_list_head.next);

    while (block != 0) {
        if (block -> size >= size) {
            *head = block->next;
            return ((char*)block) + sizeof(size_t);
        }
        head = &(block->next);
        block = block->next;
    }

    block = (free_block*)sbrk(size);
    block -> size = size;

    // Adding the new block to the head of the free block list,
    // to make it quickly available for the next allocation request.
    block -> next = free_block_list_head.next;
    free_block_list_head.next = block;

    return ((char*)block) + sizeof(size_t);
}

void standardFree(void* ptr) {
    free_block* block = (free_block*)(((char*)ptr) - sizeof(size_t));
    block -> next = free_block_list_head.next;
    free_block_list_head.next = block;
    // Add code to merge the contiguous blocks in the free block list.
    // If the immediate neighbors of the block being freed are also free,
    // they can be merged to form a larger block. This reduces fragmentation.
    mergeContiguousBlocks(free_block_list_head.next);
}

