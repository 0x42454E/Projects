#ifndef API_H
#define API_H				
			
typedef struct fsa_t fsa_t;

size_t FsaSuggestSize(size_t block_num, size_t block_size);		
/*
#insert desired values
#returns pool size including overhead count
#allocate result
*/

fsa_t *FsaInit(void *memory, size_t pool_size, size_t block_size);	
/*
#input pointer to allocated memory 
#and your initially desired block size.
#init - initiates the metadata required for the management unit fsa_t
*/

void *FsaAlloc(fsa_t* manager);						
/* provides pointer to allocation of memory by use */

void FsaFree(void *to_free, fsa_t* manager);				
/* empties one segment at a time */
					
size_t FsaCountFree(fsa_t* manager);					
/* counts free segments */				


#endif /* API_H */
