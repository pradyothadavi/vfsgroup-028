#ifndef _FREE_LIST_
#define _FREE_LIST_

/*
Group No : 28
Version No : 1.0
*/

/* This header file has the datatype definitions for the FreeList */

struct freeList{
    unsigned int ui_blockNo;
    struct s_freeList *sptr_nextFreeBlock;
};

struct freeList * s_createFreeList(int,int);

int i_getFreeDatablock(struct freeList *);

struct freeList * s_addFreeDataBlock(int);
#endif
