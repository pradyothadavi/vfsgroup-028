#include"mainHeader.h"


/*
Function Name: removefile
Description: It traverses the binary search Tree from the root with the entire path passed as parameter to get the file descriptor
Parameters : It takes a single parameter, which is the absolute path of the file to be removed
Return Type: It returns void
*/

void removefile ( char *P1 ){
	/*
		1. Search the BST with the entire path to get the file descriptor
		2. Delete that node from BST
		3. Search the nary with the given iNode number from file descriptor and remove that node from nAry tree
		4. Delete the given iNode number and delete that node from hashTable
		5. Add the iNode number to the iNode number free list
		6. Add the data block number to the dataBlock number free list

	*/
	struct fileDescriptor *fd=/* traverse BST with path  */;
	/*call the delete function in BST with the path;*/
	struct nAryTreeNode *deleteNode_nary=s_searchInode_NAryTreeNode(sPtr_rootNaryTree,fd->ui_inodeNo);
	delete_nAry(deleteNode_nary);
	v_delete(fd->ui_inodeNo,fd->cptr_fileName[]); /*deleting from hash table */
	s_inodeBlockFreeList=s_addFreeDataBlock(s_inodeBlockFreeList,fd->ui_inodeNo); /*add the inode number*/
	s_dataBlockFreeList=s_addFreeDataBlock(s_dataBlockFreeList,fd->ui_locationDataBlockN[0]);/*add the data number*/
}
