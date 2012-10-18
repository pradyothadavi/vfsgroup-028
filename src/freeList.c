#include "freeList.h"

/*
Function Name: s_createFreeList
Description: It create a list of free data blocks and inode blocks.
Parameters: It takes two parameters
            a) Starting Data Block Number
            b) Total No.of.Data Blocks
Return Type: It return a pointer which points to the starting of the list.
*/
struct freeList *s_createFreeList(int i_startingBlockNo, int i_totalBlocks){

    int i;
/*int count=1;*/
    struct freeList *start = NULL;
    struct freeList *temp = NULL;
    struct freeList *q=NULL;
	struct freeList *p=NULL;
/*	struct freeList *tempo=NULL;*/
        
    for(i=i_startingBlockNo;i<i_totalBlocks;i++)
    {
         p=(struct freeList*)malloc(sizeof(struct freeList)*1);
		 temp=start;
		
         if(start==NULL)
         {
			p->ui_blockNo=++BLOCKCOUNT;
              		start=p;
			p->sptr_nextFreeBlock=start;
			q=p;
		
			p=(struct freeList*)malloc(sizeof(struct freeList)*1);
			q->sptr_nextFreeBlock=p;
			p->ui_blockNo=i;
			p->sptr_nextFreeBlock=start;
			
         }/*if*/
         else
         {
              while(temp->sptr_nextFreeBlock != start)
              {
                   temp=temp->sptr_nextFreeBlock;
              }/*while*/
              p->ui_blockNo=i;
              p->sptr_nextFreeBlock=start;
              temp->sptr_nextFreeBlock = p;
              start->ui_blockNo=++BLOCKCOUNT;
              
              
          }/*else*/
		
     }/*for*/
     START_LL=start;

     #if DEBUG
		tempo = start;
		printf("DEBUG: Free Data Blocks Are \n");
		while((tempo != start)||(count))
		{
				count=0;
				printf("%d ",tempo->ui_blockNo);
				tempo = tempo->sptr_nextFreeBlock;
		}/*while*/
		
		/*printf("%d",tempo->ui_blockNo);*/

#endif
return START_LL;
}/*end of s_createFreeList*/

/*
Function Name: i_gets_createFreeList
Description: It gives a free data block number from the list to the calling
             module. It also deletes the block number allocated from the list.
Parameters: It takes the head pointer of the list from which the free data block
            has to be allocated. It can either be head pointer of data block list
            or head pointer of inode block list.
Return Type: It returns free data block number.
*/
int i_getFreeDatablock(struct freeList *headPtr){
		int a;/*,count=1,trial=3;*/
		struct freeList *temp=NULL;
		struct freeList *temporary=NULL;
		/*struct freeList *tempo=NULL;*/
		/*struct freeList *backup=START_LL;*/
		temporary=headPtr;/*temporary=START_LL;*/
		if(temporary->ui_blockNo==0)
		{
		return -1;
		}/*if*/
		else if(temporary->ui_blockNo==1)
		{
			a=temporary->sptr_nextFreeBlock->ui_blockNo;
			temp=temporary->sptr_nextFreeBlock;
			temporary->ui_blockNo=--BLOCKCOUNT;
			temporary->sptr_nextFreeBlock=headPtr;
			free(temp);
		
			
		}/*else if*/
		else
		{
			a=temporary->sptr_nextFreeBlock->ui_blockNo;
			temporary->ui_blockNo=--BLOCKCOUNT;
			
			
		}/*else*/
		
		if(temporary->ui_blockNo>=1)
		{
			
		temporary=headPtr;
		temp=temporary->sptr_nextFreeBlock;
		temporary->sptr_nextFreeBlock=temp->sptr_nextFreeBlock;
		free(temp);
#if DEBUG
		tempo=headPtr;
    printf("DEBUG: Free Data Blocks Are \n");
    while(tempo->sptr_nextFreeBlock != headPtr)
    {
			/*count=0;*/
			printf("%d ",tempo->ui_blockNo);
			tempo = tempo->sptr_nextFreeBlock;
	 }/*while*/
	 printf("%d ",tempo->ui_blockNo);
    printf("\n");
    /*if(trial--)*/
    /*delete(start);*/
#endif
}/*if*/
return a;
	

}/*end of i_getFreeDatablock*/

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

#if DEBUG
	struct freeList *temp=NULL;
#endif

	struct freeList *temporary=NULL;
	
	temporary=START_LL;
	
	if(temporary->sptr_nextFreeBlock==START_LL)
	{
		p->sptr_nextFreeBlock=START_LL;
		temporary->sptr_nextFreeBlock=p;
		temporary->ui_blockNo=++BLOCKCOUNT;
		p->ui_blockNo=i_dataBlockNo;
	
		}/*if*/
	
	else
	{
		p->ui_blockNo=i_dataBlockNo;
		p->sptr_nextFreeBlock=temporary->sptr_nextFreeBlock;
		temporary->sptr_nextFreeBlock=p;
		temporary->ui_blockNo=++BLOCKCOUNT;

	#if DEBUG
	temp=START_LL;
	printf("DEBUG:free data blocks are\n");
	while(temp->sptr_nextFreeBlock!=START_LL)
	{

		printf("%d ",temp->ui_blockNo);
		temp=temp->sptr_nextFreeBlock;
	}/*while*/
	printf("%d\n",temp->ui_blockNo);
#endif
	}/*else*/



return START_LL;
}  /*end of s_addFreeDataBlock*/
