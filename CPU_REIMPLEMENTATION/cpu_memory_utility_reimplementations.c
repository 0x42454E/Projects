/**
 * Custom memory utility implementations of MemSet, MemMove, and MemCpy functions,
 * replicating the behavior of standard C library functions (memset, memmove, memcpy),
 * with optimizations for memory alignment and word-sized copying.
 *
 * Author: Ben
 * Date: 2024-08
 *
 */

#include <stdlib.h>     /* malloc, free */
#include <stdint.h>     /* uintptr_t, uint8_t */

size_t 	word_size = sizeof(uintptr_t);
	
void *MemSet(void *s, int c, size_t n)
{
	size_t 		i = 0;
	size_t		block_counter = 0;
	size_t		block_counter_reminder = 0;
	char*		block = (char *)malloc(n * (sizeof(char)));
	uintptr_t*	runner = (uintptr_t *)s;
		
		for (i = 0; i < n; ++i)
		{
			block[i] = (unsigned char)c;
		}
			
		MemCpy(runner, block, n);
	
	free(block);
	
	return s;
}
 
void *MemMove(void *dest, const void *src, size_t n)
{
	uintptr_t*		runner_dest = (uintptr_t *)dest;
	const uintptr_t*	runner_src = (const uintptr_t *)src;
	uint8_t*		dest_byte = (uint8_t *)dest;
	const uint8_t*		src_byte = (uint8_t *)src;
	size_t			block_counter_reminder = 0;
	size_t			block_counter = n / word_size;
	size_t  		i = 0;
	size_t 			result_dest_alignement = (size_t)dest % word_size;
	size_t 			result_src_alignement = (size_t)src % word_size;
	
	if (!(src < dest && (size_t)src + n > (size_t)dest) && (result_dest_alignement || result_src_alignement))
	{	
			MemCpy(runner_dest, runner_src, n);
	}
	else if ((src < dest && (size_t)src + n > (size_t)dest) && (result_dest_alignement || result_src_alignement))
	{
		runner_dest += n;
		runner_src += n;
		
		while (n > word_size)
		{
			runner_src -= word_size;
			runner_dest -= word_size;
			MemCpy(runner_dest, runner_src, word_size);
			n -= word_size;
		}
		
		if (block_counter_reminder += CheckNumBlocks(n))
		{		
				for (i = 0; i < block_counter_reminder; ++i)
				{
					*dest_byte++ = *src_byte++;
				}
		}
	}
	else if (!(result_dest_alignement && result_src_alignement) && !(src < dest && (size_t)src + n > (size_t)dest))
	{	
		while (n--)
		{
			*dest_byte++ = *src_byte++;
		}
	}
	else
	{
		runner_dest += (uint8_t *)(n - 1);
		runner_src += (uint8_t *)(n - 1);
		
		while (n--)
		{
			*runner_dest-- = *runner_src--;
		}
	}
		
	return dest;
}

void *MemCpy(void *dest, const void *src, size_t n)
{
	uintptr_t*		runner_dest = (uintptr_t *)dest;
	const uintptr_t*	runner_src = (const uintptr_t *)src;
	size_t			block_counter_reminder = 0;
	size_t			block_counter = n / word_size;
	size_t 			i = 0;
	size_t 			result_dest_alignement = (size_t)dest % word_size;
	size_t 			result_src_alignement = (size_t)src % word_size;
	uint8_t*		dest_byte = (uint8_t *)dest;
	uint8_t*		src_byte = (uint8_t *)src;
		
		if (result_dest_alignement || result_src_alignement)
		{
			for (; i < n; ++i)
			{
				*dest_byte++ = *src_byte++;
			}
		}
		else
		{
			block_counter_reminder += CheckNumBlocks(n);
			
			for (i = 0; i < block_counter; ++i)
			{
				*runner_dest++ = *runner_src++;
			}
			
			for (i = 0; i < block_counter_reminder; ++i)
			{
				*dest_byte++ = *src_byte++;				
			}
		}
	
	return dest;
}

size_t CheckNumBlocks(size_t n)
{	
	return n % word_size;
}


