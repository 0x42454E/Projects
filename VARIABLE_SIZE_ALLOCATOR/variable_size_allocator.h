#ifndef VSA_H
#define VSA_H

/* API- Varialbe Size allocator*/


typedef struct vsa vsa_t;


/* Function to initialize the manager */
vsa_t *VsaInit(size_t total_memory, void *start_pool_memory);

/* Function to allocate a specific size of memory block */
void *VsaAlloc(vsa_t *mngr ,size_t block_size);

/* Function to free a block of memory */
void VsaFree(void *to_free );

/* Function to detrmine the largest available block of memory */
size_t LargestFree(vsa_t * manager);


/*comments
*vsa_t manager include paramter that show the largest_chunk_available
*every block contains pointer to vsa_manager;
*/


#endif /* VSA_H */
