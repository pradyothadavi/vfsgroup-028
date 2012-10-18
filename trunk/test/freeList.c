#include "freeList.h"
#include <stdio.h>
#include <stdlib.h>

/*
Function Name: s_createFreeList
Description: It create a list of free data blocks and inode blocks.
Parameters: It takes two parameters
            a) Starting Data Block Number
            b) Total No.of.Data Blocks
Return Type: It return a pointer which points to the starting of the list.
*/
struct freeList * s_createFreeList(int i_startingBlockNo, int i_totalBlocks){
    int i,count=1;
    struct freeList *start = NULL;
    struct freeList *temp = NULL;
    struct freeList *q=NULL;
        
    for(i=i_startingBlockNo;i<i_totalBlocks;i++)
    {
         struct freeList *p=(struct freeList*)malloc(sizeof(struct freeList)*1);
		 temp=start;
		
         if(start==NULL)
         {
			p->ui_blockNo=++BLOCKCOUNT;
              		start=p;
			p->sptr_nextFreeBlock=start;
			q=p;
		
			struct freeList *p=(struct freeList*)malloc(sizeof(struct freeList)*1);
			q->sptr_nextFreeBlock=p;
			p->ui_blockNo=i;
			p->sptr_nextFreeBlock=start;
			
         }
         else
         {
              while(temp->sptr_nextFreeBlock != start)
              {
                   temp=temp->sptr_nextFreeBlock;
              }
              p->ui_blockNo=i;
              p->sptr_nextFreeBlock=start;
              temp->sptr_nextFreeBlock = p;
              start->ui_blockNo=++BLOCKCOUNT;
              
              
          }
		
     }
     START_LL=start;

     #if 1
		struct freeList *tempo=NULL; 
	
		tempo = start;
		printf("DEBUG: Free Data Blocks Are ");
		while((tempo != start)||(count))
		{
				count=0;
				printf("%d ",tempo->ui_blockNo);
				tempo = tempo->sptr_nextFreeBlock;
		}
#endif
return START_LL;
}

/*
Function Name: i_getFreeDataBlock
Description: It gives a free data block number from the list to the calling
             module. It also deletes the block number allocated from the list.
Parameters: It takes the head pointer of the list from which the free data block
            has to be allocated. It can either be head pointer of data block list
            or head pointer of inode block list.
Return Type: It returns free data block number.
*/
int i_getFreeDatablock(struct freeList *headPtr){
                int a;
		struct freeList *temp=NULL;
		struct freeList *temporary=NULL;
		
		temporary=headPtr;
		if(temporary->ui_blockNo==0)
		{
		return -1;
		}
		else if(temporary->ui_blockNo==1)
		{
			a=temporary->sptr_nextFreeBlock->ui_blockNo;
			temp=temporary->sptr_nextFreeBlock;
			temporary->ui_blockNo=--BLOCKCOUNT;
			temporary->sptr_nextFreeBlock=headPtr;
			free(temp);
		
			
		}
		else
		{
			a=temporary->sptr_nextFreeBlock->ui_blockNo;
			temporary->ui_blockNo=--BLOCKCOUNT;
			
			
		}
		
		if(temporary->ui_blockNo>=1)
		{
			
		temporary=headPtr;
		temp=temporary->sptr_nextFreeBlock;
		temporary->sptr_nextFreeBlock=temp->sptr_nextFreeBlock;
		free(temp);
#if 1
		temporary=headPtr;
    printf("DEBUG: Free Data Blocks Are ");
    while(temporary->sptr_nextFreeBlock != headPtr)
    {
			
			printf("%d ",temporary->ui_blockNo);
			temporary = temporary->sptr_nextFreeBlock;
	 }
	 printf("%d ",temporary->ui_blockNo);
    printf("\n");
#endif
}
return a;
}

/*
Function Name: s_addFreeDataBlock
Description: It adds the data block number to the free list that was released.
Parameters: It takes the free data block number that has to be added to the
            free list.
Return Type: It returns the head pointer of the list to which the free data
             block is added.
*/
struct freeList * s_addFreeDataBlock(int i_dataBlockNo){
    struct freeList *p=(struct freeList*)malloc(sizeof(struct freeList)*1);
	struct freeList *temp=NULL;
	struct freeList *temporary=NULL;
	
	temporary=START_LL;
	
	if(temporary->sptr_nextFreeBlock==START_LL)
	{
		p->sptr_nextFreeBlock=START_LL;
		temporary->sptr_nextFreeBlock=p;
		temporary->ui_blockNo=++BLOCKCOUNT;
		p->ui_blockNo=i_dataBlockNo;
	
		}
	
	else
	{
		p->ui_blockNo=i_dataBlockNo;
		p->sptr_nextFreeBlock=temporary->sptr_nextFreeBlock;
		temporary->sptr_nextFreeBlock=p;
		temporary->ui_blockNo=++BLOCKCOUNT;
	#if 1
	temp=START_LL;
	while(temp->sptr_nextFreeBlock!=START_LL)
	{

		printf("%d ",temp->ui_blockNo);
		temp=temp->sptr_nextFreeBlock;
	}
	printf("%d\n",temp->ui_blockNo);
	}
#endif
return START_LL;
}  
