#include"mainHeader.h"
#include"nAryTree.h"
#include"fileDescriptor.h"
#include"block.h"
#include<global.h>
#include<string.h>
#include "limits.h"
#include "fileSystemOps.h"
#include"vfserrorcodes.h"

/*
Function Name: removefile
Description: It traverses the binary search Tree from the root with the entire path passed as parameter to get the file descriptor
Parameters : It takes a single parameter, which is the absolute path of the file to be removed
Return Type: It returns void
*/

void removefile ( char *P1 ){
	/*
		1. Search the nary with the entire path to get the file descriptor
		2. Delete that node from BST
		3. Search the nary with the given iNode number from file descriptor and remove that node from nAry tree
		4. Delete the given iNode number and delete that node from hashTable
		5. Add the iNode number to the iNode number free list
		6. Add the data block number to the dataBlock number free list

	*/
	struct nAryTreeNode *nary= NULL;
	char *vfsLabel;
	char *token;
	struct fileDescriptor *fd;
	char *ndir= NULL;
	ndir=P1;
	vfsLabel="demo";
	nary=sPtr_rootNAryTree;
	token=strtok(ndir,"/");
	
	while(token!=NULL)
             {  
                 
             i_noOfCharacters=strlen(token)+1;
             nary=s_searchNAryTreeNode(nary,token);

              if(NULL==nary)
                 {   
                     printf(ERR_VFS_REMOVEFILE_01);
                                     
                 }
                 
               token=strtok(NULL,"/");
            }

	fd=nary->s_inode;
	v_deleteNAryTreeNode(nary);
	v_delete(fd->ui_inodeNo,fd->cptr_fileName[]); /*deleting from hash table */
	s_inodeBlockFreeList=s_addFreeDataBlock(s_inodeBlockFreeList,fd->ui_inodeNo); /*add the inode number*/
	s_dataBlockFreeList=s_addFreeDataBlock(s_dataBlockFreeList,fd->ui_locationDataBlockN[0]);/*add the data number*/
}






