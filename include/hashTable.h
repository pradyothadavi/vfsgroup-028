#ifndef _HASH_TABLE_
#define _HASH_TABLE_
#include "fileSystemOps.h"
/*
Group No: 028
Version No: 1.0
*/

#define NOOFBUCKETS 26

struct chain{
    char c_fileName[VFS_NAMELEN];
    int i_inodeNo;
    struct chain *next;
};

extern struct chain *hashTableBucket[26];
void v_initializeHashTable();

void v_loadHashTable(unsigned int inode,char fileName[]);

int i_calculateIndex(char fileName[]);

struct chain* searchHashTable(char fileArray[]);

void delete(int iNode,char fileArray[]);


#endif
