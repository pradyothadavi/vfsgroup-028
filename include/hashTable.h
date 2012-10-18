#ifndef _HASH_TABLE_
#define _HASH_TABLE_

/*
Group No: 028
Version No: 1.0
*/

#define NOOFBUCKETS 26

struct hashBucket{
    char c_fileName[VFS_NAMELEN];
    int i_inodeNo;
    struct hashBucket *next;
};


v_initializeHashTable(struct hashBucket *);

v_loadHashTable(struct hashBucket *,struct nAryTreeNode *);

#endif
