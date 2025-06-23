/******************************************************************************
 * EXT2 File System Parser and Modifier
 * ----------------------------------------------------------------------------
 * Implements low-level EXT2 file system operations using raw disk I/O.
 * 
 * Features:
 * - `FSOpen` / `FSClose`: Open and close raw EXT2 disk image
 * - `GetInode`: Retrieve inode number of a file given a path
 * - `PrintFileContent`: Read and print file contents using inode
 * - `Chmode`: Change file permissions (mode bits) given an inode
 * 
 * Internals:
 * - Direct manipulation of superblock, group descriptor table, inode table
 * - Manual directory traversal and EXT2 inode interpretation
 * - Uses `pread` / `pwrite` and low-level offsets into disk structures
 *
 * Intended for educational or forensic use; assumes EXT2 layout correctness.
 ******************************************************************************/
