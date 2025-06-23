#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdint.h>
#include "ext2_parsing.h"

#define _XOPEN_SOURCE 500 
#define POSIX_C_SOURCE 200809L
#define SUPERBLOCK    1024
#define	BGT	      4096
#define EXT2_S_IFDIR  0x4000 
#define EXT2_S_IFREG  0x8000  

struct fs_s
{
	int  		mount_point;
	long 		inode_num;
	void*		file_descriptor;
	size_t 		block_group_num;
	uint32_t	block_size;
	uint32_t	inode_size;
	uint32_t	blocks_count;
	uint32_t	num_of_groups;
	uint32_t	cur_inode_table;
	uint32_t	first_data_block;
	uint32_t	inode_table_offset;
	uint32_t	inodes_per_group;
};

ssize_t pread(int fd, void *buf, size_t count, off_t offset); 
ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);  
char *strdup(const char *s);
static long GetDirectory(FS_t* file_system, long inode_num, const char* path_name);

FS_t* FSOpen(const char* disk_name)
{
	FS_t* file_system = malloc(sizeof(FS_t));
	if (!file_system)
	{
		fprintf(stderr, "malloc failed\n");
		return NULL;
	}
	
	file_system->mount_point = open(disk_name, O_RDWR); 
	if (file_system->mount_point < 0)
	{
		fprintf(stderr, "opening file system failed %s\n",  strerror(errno));
		free(file_system);
		return NULL;
	}
	
	return file_system;
}


int FSClose(FS_t* file_system)
{
	int result = close(file_system->mount_point);
	file_system->file_descriptor = NULL;

	free(file_system);
	
	return result;
}

/*****************************************************************************************
 * find inode num based on file_path 
 * assign values to file_system manager
 * traverse place holder to group descriptor -> inode table -> directory root -> file_path
 * Time Complexity: O()
 * Return inode number of a file, -1 if not found. 
 */
long GetInode(FS_t* file_system, const char* file_path)
{
	size_t	sz = 0;
	long	result = 0;
	void* 	place_holder = NULL;
	void*	buffer = malloc(SUPERBLOCK);
	
	/*****************************************************************************************
	 * go through SUPERBLOCK
	 * and assign values to manager
	 */

	if (!buffer)
	{
		fprintf(stderr, "malloc fs failed\n");
		return -1;
	}

	 if (lseek(file_system->mount_point, SUPERBLOCK, SEEK_SET) == -1 ||
        read(file_system->mount_point, buffer, SUPERBLOCK) != SUPERBLOCK) 
        {
       		perror("Failed to access superblock\n");
       		free(buffer);
       		return -1;
   	}

	place_holder = buffer;

	file_system->block_size = 1024 << ((struct ext2_super_block*)place_holder) -> s_log_block_size;
	file_system->first_data_block = ((struct ext2_super_block*)place_holder) -> s_first_data_block;
	file_system->blocks_count = ((struct ext2_super_block*)place_holder) -> s_blocks_count;
	file_system->inode_size = ((struct ext2_super_block*)place_holder) -> s_inode_size;
	file_system->inodes_per_group = ((struct ext2_super_block*)place_holder) -> s_inodes_per_group;
	if (((struct ext2_super_block*)place_holder) -> s_inodes_per_group == 0) 
	{
    		fprintf(stderr, "initiation from SUPERBLOCK Error\n");
    	}
    	
	file_system->num_of_groups = ((struct ext2_super_block*)place_holder) -> s_inodes_count + (((struct ext2_super_block*)place_holder) -> s_inodes_per_group - 1) / ((struct ext2_super_block*)place_holder) -> s_inodes_per_group;
	
	/*****************************************************************************************
	 * go to GDT
	 * and access ROOT_DIRECTORY in the second block
	 */
	 			
	free(buffer);
	buffer = malloc(sizeof(struct ext2_group_desc));
	if (!buffer)
	{
		fprintf(stderr, "malloc fs failed\n");
	}
	
	sz = lseek(file_system->mount_point, BGT, SEEK_SET);
	
	if ((int)sz == -1 || sz != BGT)
	{
	    perror("lseek BGT failed\n");
	    free(buffer);
	    return -1; 
	}

	sz = read(file_system->mount_point, buffer, sizeof(struct ext2_group_desc));
	if ((int)sz == -1 || sz != sizeof(struct ext2_group_desc))
	{
	    perror("read BGT failed\n");
	    free(buffer);
	    return -1; 
	}	
	 
	place_holder = buffer;
		    		
	file_system->cur_inode_table = ((struct ext2_group_desc *)place_holder) -> bg_inode_table;
		
	result = GetDirectory(file_system, 2, (char*)file_path);
	if (result > 0)
	{				
		printf("result = %ld\n", result);
	}
	
	file_system->inode_num = result;

	return result;
}


/****************************************************************************** 
 * Prints file's content to the screen 
 * *file_system: pointer to the file system
 * *inode_num: Inode of the file by the path (GetInode())
 * Time Complexity: O(1)
 */
void PrintFileContent(FS_t* file_system, long inode_num, void* external_buffer) 
{
	void*		data_block = NULL;	
	void*		place_holder = NULL;
	void*		buffer = malloc(sizeof(struct ext2_inode));	 
	uint32_t  	block_ptr[15];
	size_t		i = 0;
	size_t		sz = 0;
	size_t 		seek_position = (inode_num - 1) * file_system->inode_size +  file_system->cur_inode_table * file_system->block_size;
	    
	if (block_ptr == NULL) 
	{
		perror("Failed to allocate memory for block_ptr\n");
		return;
	}
	    
	if (buffer == NULL) 
	{
		perror("Failed to allocate memory for buffer\n");
		return;
	}
	
	sz = lseek(file_system->mount_point, seek_position, SEEK_SET);
	if ((int)sz == -1 || sz != seek_position)
	{
	    perror("lseek get data failed\n");
	    free(buffer);
	    return; 
	}
	
 	sz = read(file_system->mount_point, buffer, (sizeof(struct ext2_inode))); 
	if ((int)sz == -1 || sz != sizeof(struct ext2_inode))
	{
	    perror("read get data failed\n");
	    free(buffer);
	    return; 
	}	
	
	place_holder = buffer;
	
	memcpy(block_ptr, ((struct ext2_inode*)place_holder)->i_block, sizeof(block_ptr));
	
	data_block = malloc(file_system->block_size);
	if (data_block == NULL) 
	{
		perror("Failed to allocate memory for data_block\n");
		free(buffer);
		return;
	}
		
	for (i = 0; i < 12; ++i) 
	{
		if (block_ptr[i] == 0) 
		break;
		
		seek_position = block_ptr[i] * file_system->block_size;
		
		sz = lseek(file_system->mount_point, seek_position, SEEK_SET);
		if ((int)sz == -1 || sz != seek_position)
		{
		   	perror("lseek copy data failed\n");
		   	free(data_block);
		   	free(buffer);
		   	return; 
		}
		
	 	sz = read(file_system->mount_point, buffer, file_system->block_size); 
		if ((int)sz == -1 || sz != file_system->block_size)
		{
		  	perror("read copy data failed\n");
		    	free(data_block);
		    	free(buffer);		    
		    	return; 
		}	
		
		if (!memcpy(external_buffer, buffer, file_system->block_size))
		{
			perror("read copy data failed\n");
		   	free(data_block);
		    	free(buffer);		    
		    	return; 
		}
		
		external_buffer = (uint8_t*)external_buffer + file_system->block_size;
	 }
	 
	free(buffer);
}



/******************************************************************************
 * traverse the directories till desired name if found and return its inode num
 * check if inode_num is a directory mode
 * move place_holder to directory struct and traverse directory list
 */
static long GetDirectory(FS_t* file_system, long inode_num, const char* path_name) 
{
	int 	  	i = 0;
	int	  	found = 0;
	char*      	path_copy = strdup(path_name);
	char* 	  	token = strtok(path_copy, "/");
	void*	   	place_holder = NULL;
	void*		data_block = NULL;	
	void*	  	buffer = NULL;
	struct     	ext2_dir_entry* dir_entry;
	uint32_t   	block_ptr[15];
	size_t	 	sz = 0;
	size_t     	rec_len = 0;
  	size_t	  	seek_position = (inode_num - 1) * file_system->inode_size + (file_system->cur_inode_table * file_system->block_size);
	
	if (!path_name || !token) 
	{
		perror("invalid path_name\n");
		free(path_copy);
		return -1;
	}
	
	/*****************************************************************************************
	 * access desired inode
	 * and locate file by path_name
	 */
	
	buffer = malloc(sizeof(struct ext2_inode));
	if (buffer == NULL) 
	{
		perror("Failed to allocate memory for buffer\n");
		free(buffer);
		free(path_copy);
		return -1;
	}
	   
	sz = lseek(file_system->mount_point, seek_position, SEEK_SET);
	if ((int)sz == -1 || sz != seek_position)
	{
	  	perror("lseek seek_position in GetDirectory failed\n");
	  	free(buffer);
		free(path_copy);
	   	return -1; 
	}

	sz = read(file_system->mount_point, buffer, sizeof(struct ext2_inode)); 
	if (sz != sizeof(struct ext2_inode)) 
	{
      		   perror("Failed to read inode\n");
       		   free(buffer);
     		   free(path_copy);
      		   return -1;
   	 }
	
	place_holder = buffer;
        	
	if ((((struct ext2_inode*)buffer)->i_mode & EXT2_S_IFDIR) != EXT2_S_IFDIR)
	{
		fprintf(stderr, "Not a directory inode\n");
		return -1;
	}		
	
	memcpy(block_ptr, ((struct ext2_inode*)place_holder) -> i_block, sizeof(block_ptr));
	    
	data_block = malloc(file_system->block_size);
	if (data_block == NULL) 
	{
		perror("Failed to allocate memory for data_block\n");
		free(buffer);
		free(path_copy);
		return -1;
	}
		

	while (token) 
	{
		found = 0;

        	for (i = 0; i < 12; ++i) 
       		{
            		if (block_ptr[i] == 0) 
            		break;
            
           		rec_len = 0;
			
			seek_position = block_ptr[i] * file_system->block_size;
   			
   			sz = lseek(file_system->mount_point, seek_position, SEEK_SET);
   			if ((int)sz == -1 || sz != seek_position)
			{
			  	perror("lseek seek_position in GetDirectory failed\n");
			  	free(buffer);
				free(path_copy);
			   	return -1; 
			}
			
			sz = read(file_system->mount_point, data_block, file_system->block_size); 
			if (sz != file_system->block_size) 
			{
		      		   perror("Failed to read data block\n");
		       		   free(buffer);
		     		   free(path_copy);
		      		   return -1;
		   	}
			
			place_holder = data_block;
			
				while (rec_len < file_system->block_size) 
				{
					dir_entry = (struct ext2_dir_entry*)((uint8_t*)place_holder + rec_len);
					if (!strncmp(dir_entry->name, token, dir_entry->name_len))
					{
						
						found = 1;
				   	  	file_system->inode_num = dir_entry->inode; 
				  	  	token = strtok(NULL, "/");
				    	  	break;
					}				
					
					rec_len += dir_entry->rec_len;	
				}
			
			
			if (found)
			{
				break;
			} 
			
			else
			{
			    fprintf(stderr, "File not found: %s\n", path_name);
			    return -1;
			}
		}
	}

	free(path_copy);
	free(data_block);
	
    return file_system->inode_num;
}

/****************************************************************************** 
 * Changes permissions of a file. Return status of success or failure.
 * *file_system: pointer to the file system
 * *inode_num: Inode of the file by the path (GetInode())
 * *new_mode: Permissions modifiers requested by the user.
 * Time Complexity: O(1)
 */
int Chmode(FS_t* file_system, long inode_num, char *new_mode)
{
	int	 val = 0;
	int	 length = strlen(new_mode) - 1;
	void* 	 buffer = malloc(sizeof(struct ext2_group_desc));
	size_t	 sz = 0;
	size_t	 temp = inode_num / file_system->num_of_groups;
	uint16_t mod_bits = 0;
	  
	/*****************************************************************************************
	 * A variable to store changes
	 * and cast them to switch later
	 */
	 
	struct change
	{
		unsigned type:4;	
		unsigned set_uid:1;
		unsigned set_gid:1;
		unsigned sticky:1;
		unsigned owner:3;
		unsigned group:3;
		unsigned other:3;
	}mod;
	
	new_mode = new_mode + length;
	
	val = atoi(new_mode);

	mod.other = val & 7;

	--new_mode;
	
	val = atoi(new_mode) / 10;

	mod.group = val & 7;

	--new_mode;
	
	val = atoi(new_mode) / 100;

	mod.owner = val & 7;
	
	if (length == 4)
	{
		--new_mode;
		val = atoi(new_mode);
		
		mod.sticky = val & 1; 		
		mod.set_gid = (val >> 1) & 1;  
		mod.set_uid = (val >> 2) & 1;
	}
	
	if (!buffer) 
	{
		perror("Failed to allocate memory for buffer\n");
		return -1;
	}
	
	if (lseek(file_system->mount_point, 4096 + temp * (sizeof(struct ext2_group_desc)), SEEK_SET) == -1) 
	{
		      perror("lseek failed\n");
		      return -1;
	}
	
	sz = read(file_system->mount_point, buffer, (sizeof(struct ext2_group_desc)));
	if (sz != (sizeof(struct ext2_group_desc))) 
	{
      		   perror("Failed to read GDT\n");
       		   free(buffer);;
      		   return -1;
   	 }
   	 
	temp = (inode_num % file_system->inodes_per_group) * (sizeof(struct ext2_inode)) + ((struct ext2_group_desc*)buffer) -> bg_inode_table * file_system->block_size;
	
	if (lseek(file_system->mount_point, temp, SEEK_SET) == -1) 
	{
		      perror("lseek failed\n");
		      return -1;
	}
	
	buffer = realloc(buffer, (sizeof(struct ext2_inode)));
	if (!buffer)
	{
      		   perror("Failed realloc to ext2_inode\n");
       		   free(buffer);;
      		   return -1;
   	 }

	sz = read(file_system->mount_point, buffer, (sizeof(struct ext2_inode)));
	if (sz != (sizeof(struct ext2_inode)))
	{
      		   perror("Failed to read inode\n");
       		   free(buffer);;
      		   return -1;
   	 }
   	
   	/*****************************************************************************************
	 * go through all i_mode members 
	 * and implement adaptation
	 * excluding change type
	 */
	
   	mod.type = (((struct ext2_inode*)buffer) -> i_mode) >> 12;
	
   	mod_bits |= mod.type;
   	mod_bits <<= 1;
   	
   	mod_bits |= mod.set_uid;
   	mod_bits <<= 1;
   	
   	mod_bits |= mod.set_gid;
   	mod_bits <<= 1;
   	
   	mod_bits |= mod.sticky;
   	mod_bits <<= 3;
   	
   	mod_bits |= mod.owner;
   	mod_bits <<= 3;
   	
   	mod_bits |= mod.group;
   	mod_bits <<= 3;
   	
   	mod_bits |= mod.other;
	
   	if (pread(file_system->mount_point, buffer, 2, temp) != 2)
   	{
   		perror("Failed to update permissions\n");
		return -1;
   	}
   	
   	if (pwrite(file_system->mount_point, &mod_bits, 2, temp) != 2)
   	{
   		perror("Failed to update permissions\n");
		return -1;
   	}
   	
  	
	val = memcmp(&(((struct ext2_inode*)buffer) -> i_mode), &mod_bits, 2);
  	
  	free(buffer);
  	
	return val;
}
