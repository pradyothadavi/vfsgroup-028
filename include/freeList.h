#ifndef _FREE_LIST_
#define _FREE_LIST_

#include<stdio.h>
#include<stdlib.h>

/*
Group No : 28
Version No : 1.0
*/


/* This header file has the datatype definitions for the FreeList */
struct freeList{
    unsigned int ui_blockNo;
    struct freeList *sptr_nextFreeBlock;
};

int BLOCKCOUNT;
struct freeList *START_LL;

struct freeList * s_createFreeList(int,int);

int i_getFreeDatablock(struct freeList *);

struct freeList *s_addFreeDataBlock(int);

#endif
