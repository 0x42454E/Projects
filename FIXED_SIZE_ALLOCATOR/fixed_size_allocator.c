/***************************************************************
 * Fixed Size Allocator (FSA) Implementation
 * -------------------------------------------------------------
 * Author: Ben 
 *
 * Overview:
 * This code implements a simple Fixed Size Allocator (FSA),
 * designed to manage a memory pool divided into equal-sized blocks.
 * It supports:
 *   - Suggesting total memory size needed for N blocks
 *   - Initialization of the allocator (`FsaInit`)
 *   - Fixed-size memory allocation (`FsaAlloc`)
 *   - Memory deallocation (`FsaFree`)
 *   - Tracking free blocks (`FsaCountFree`)
 *
 * Notes:
 * - Only one freed block is tracked (`reserve_after_free`)
 * - Intended for use-cases with predictable block sizes and lifetimes
 * - Padding and alignment are handled based on `WORD_SIZE`
 *
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WORD_SIZE  sizeof(size_t)

typedef struct
{
	void*	end_of_space;
	size_t 	block_size;
	void*	next_free_block;
	void*	reserve_after_free;
	size_t	num_free_blocks;
	
}fsa_t;

fsa_t manager;

size_t FsaSuggestSize(size_t block_num, size_t block_size)
{		
	size_t 	result = (block_num * block_size) + (sizeof(manager));
	size_t 	padding = WORD_SIZE - (block_size % WORD_SIZE);
	
	result += padding;
	result += WORD_SIZE - (result % WORD_SIZE);
		
		return result;
}

fsa_t *FsaInit(void *memory, size_t pool_size, size_t block_size)
{	
	manager.reserve_after_free = NULL;	
	manager.next_free_block = memory;
	manager.num_free_blocks = pool_size / block_size;
	manager.block_size = block_size;
	manager.end_of_space = (char*)memory + pool_size;
	
	return &manager;
}

void *FsaAlloc(fsa_t* manager)
{
	void*	temp;
	
	if (manager -> reserve_after_free == NULL)
	{
		temp = manager -> next_free_block;
		manager -> next_free_block = (char*)manager -> next_free_block + manager -> block_size;
		if (manager -> next_free_block == manager -> end_of_space)
		{
			perror("last available allocation\n end of space\n");
		}
	}
	else
	{
		temp = manager -> reserve_after_free;
		manager -> reserve_after_free = NULL;
	}
		--manager -> num_free_blocks;
	return temp;
}

void FsaFree(void *to_free, fsa_t* manager)	
{
	manager -> reserve_after_free = manager -> next_free_block;
	memset(to_free, 0, manager -> block_size);
	++manager -> num_free_blocks;
}

size_t FsaCountFree(fsa_t* manager)
{
	return manager -> num_free_blocks;
}


