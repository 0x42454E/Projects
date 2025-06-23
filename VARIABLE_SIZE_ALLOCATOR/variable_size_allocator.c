/***************************************************************
 * Variable Size Allocator (VSA) Implementation
 * -------------------------------------------------------------
 * Author: Ben 
 *
 * Overview:
 * This code implements a basic memory allocator (similar to malloc/free),
 * which manages a given memory pool using a custom structure (`vsa_t`).
 * It tracks allocations using overhead metadata and supports:
 *   - First-fit memory allocation (`VsaAlloc`)
 *   - Deallocation with defragmentation (`VsaFree`)
 *   - Finding the largest contiguous free block (`LargestFree`)
 *   - Handling fragmented memory regions (`FindFragmentedAlloc`)
 *
 * Key Features:
 * - Metadata stored alongside each block: size, next pointer, status.
 * - Fragmentation-aware allocation mode.
 * - Magic numbers used to mark free (`0xFFF00FFF`) and used (`0xFFFFFFFF`) blocks.
 *
 * Usage:
 * 1. Initialize with `VsaInit(total_size, pool_ptr)`
 * 2. Allocate with `VsaAlloc(manager, size)`
 * 3. Free blocks with `VsaFree(ptr)`
 * 4. Query max free block with `LargestFree(manager)`
 *
 ****************************************************************/


#include <stdlib.h>
#include <string.h>
#include "vsa.h"
#define OVERHEAD sizeof(size_t)
#define EMPTY_MAGIC_NUM	0xFFF00FFF
#define USED_MAGIC_NUM	0xFFFFFFFF

void* FindFragmentedAlloc(size_t block_size, vsa_t* manager);
 
typedef struct vsa
{
	void*	memory_start;
	void*	memory_end;
	void*	memory_curr;
	char	initiate_fragmentation_managing_mode;
	
};

vsa_t manager;

vsa_t *VsaInit(size_t total_memory, void *start_memory_pool) 
{
	manager.memory_start = start_memory_pool;
	manager.memory_curr = start_memory_pool;
	manager.memory_end = (char*)start_memory_pool + total_memory;
	manager.initiate_fragmentation_managing_mode = 0;
	
	return &manager;
}

void *VsaAlloc(vsa_t *manager ,size_t block_size) 
{
	void*	temp = manager->memory_curr;
	size_t	overhead_value_assignment;
	size_t	status = USED_MAGIC_NUM;
	void*	initiator = NULL;
	
	block_size = OVERHEAD - (block_size % OVERHEAD);
	
	overhead_value_assignment = block_size;
	
	if (manager->initiate_fragmentation_managing_mode)
	{
		temp = FindFragmentedAlloc(block_size, manager);
	}
	else if (((char*)manager->memory_curr + block_size + 3 * OVERHEAD) > (char*)manager->memory_end)
	{
			manager->initiate_fragmentation_managing_mode = 1;
			printf("fragmentation mode initiated. Use Alloc function again\n");
	}
	else
	{
		memcpy(temp, &overhead_value_assignment, OVERHEAD);
		temp = (char*)temp + OVERHEAD;
		memcpy(temp, &initiator, OVERHEAD);
		temp = (char*)temp + OVERHEAD;
		memcpy(temp, &status, OVERHEAD);
		temp = (char*)temp + OVERHEAD;
		manager->memory_curr = (char*)manager->memory_curr + block_size + 3 * OVERHEAD;
	}
	
	return temp;
}

void VsaFree(void *to_free)
{
	size_t 	change_status_to_free = EMPTY_MAGIC_NUM;
	void*	runner = to_free;
	void**	temp;
	
	runner = (char*)runner - OVERHEAD - OVERHEAD;
		
	if (runner == NULL)
	{
		to_free = (char*)to_free - OVERHEAD;
		memcpy(to_free, &change_status_to_free, OVERHEAD);
	}
	else
	{
		to_free = (char*)to_free - OVERHEAD;
		memcpy(to_free, &change_status_to_free, OVERHEAD);
		
		while (runner != NULL)
		{
			temp = (void**)runner;
			runner = *temp;
			memcpy(runner, &change_status_to_free, OVERHEAD);
		}
	}
}

size_t LargestFree(vsa_t* manager)
{
	size_t 		distance = 0;
	size_t		temp_distance = 0;
	size_t*		runner = (size_t*)manager->memory_start;
	size_t**	temp = NULL;
	size_t**	from = NULL;
	size_t*		to = NULL;
	
	while ((char*)runner <= (char*)manager->memory_end)
	{
		if (*runner == EMPTY_MAGIC_NUM)
		{
			from = runner;
			temp = runner;
		}
		
		if (*runner == USED_MAGIC_NUM && runner > *temp || (char*)runner == (char*)manager->memory_end)
		{
			to = runner;
			temp_distance = (char*)to - (char*)from;
		}
		
		if (temp_distance > distance)
		{
			distance = temp_distance; 
		}
			++runner;
	}
	
	return distance;
}

void* FindFragmentedAlloc(size_t block_size, vsa_t* manager) 
{
	size_t 	i = 0;
	size_t	j = 1;
	size_t 	memory_pool_length = (char*)manager->memory_end - (char*)manager->memory_start;
	size_t 	extract_overhead_size = 0;
	size_t*	general_runner = (size_t*)manager->memory_start;
	size_t*	runner;
	void*	start = NULL;
	void*	temp = NULL;
	size_t	status = USED_MAGIC_NUM;
	size_t	restatus = EMPTY_MAGIC_NUM;
	size_t	sum = 0;

	for (;i < memory_pool_length / OVERHEAD; ++i)
	{
		j = 1;
		
		if (general_runner[i] == EMPTY_MAGIC_NUM)
		{
			runner = &general_runner[i];
			sum_ptr = runner;
			start = runner;
			temp = runner;
		
			runner = (char*)runner - 2 * OVERHEAD;
			extract_overhead_size += *(size_t*)runner;
			sum += *(size_t*)runner;
			runner = (char*)runner + OVERHEAD;
			
			if (extract_overhead_size >= block_size)
			{
				memcpy(temp, &status, OVERHEAD);
				break;
			}
			else if (general_runner[i+j] == EMPTY_MAGIC_NUM)
			{
				while (general_runner[i+j] == EMPTY_MAGIC_NUM)
				{
					*(size_t*)runner = (size_t*)temp;
					runner = (char*)runner - 2 * OVERHEAD;
					memcpy(runner, &status, OVERHEAD);
					extract_overhead_size += *(size_t*)runner;
					sum += *(size_t*)runner;
					if (extract_overhead_size >= block_size)
					{
						memcpy(temp, &status, OVERHEAD);
						break;
					}
						temp = general_runner[i+j];
						++j;
				}
			}
		}
		
		if (extract_overhead_size != 0)
		{
			temp = runner;
			
			
			while (*temp == USED_MAGIC_NUM)
			{
				runner = temp;
				memcpy(runner, &restatus, OVERHEAD);
				runner = (char*)runner - OVERHEAD;
				(size_t*)temp = *(size_t*)runner;
				temp = (char*)temp - OVERHEAD;
			}
		}
	}
	
	if (start == NULL || extract_overhead_size < block_size)
	{
		perror("Allocation is not possible\n");
		return;
	}
	
	*(size_t*)start = sum;
	
	return start;
}
