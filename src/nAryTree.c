#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nAryTree.h"
#include "fileSystemOps.h"
#include "freeList.h"

/*
Function Name: s_loadFileSystem
Description: It loads the file system into the main memory in the form of 
             n-Ary Tree.
Parameters: It takes a single parameter, which is the root inode number.
Return Type: It return a pointer which points to the root of the n-Ary Tree.
*/
struct nAryTreeNode * s_loadFileSystem(int i_rootInodeNo, FILE * fpVfs,struct mainHeader *s_superBlock){

    struct fileDescriptor s_inode;
    struct directoryEntry s_dientry;
    
    struct nAryTreeNode *root = NULL;
    struct nAryTreeNode *currentNode = NULL;
   
    int i_retVal = 0;
    
    if((fseek(fpVfs,i_rootInodeNo*VFS_BLOCKSIZE,SEEK_SET)) == -1){
         printf("ERROR: Cannot fetch the Inode Block \n");
    }

    if((i_retVal=fread(&s_inode,sizeof(struct fileDescriptor),1,fpVfs)) != 1){
         printf("ERROR: Cannot read a Data Block \n");
    }

    currentNode = s_createNAryTreeNode(i_rootInodeNo,fpVfs);
    if(NULL == root){
         root = s_insertNAryTreeNode(root,currentNode);
    }
    if(s_inode.c_fileType[0] == 'd'){
         if((fseek(fpVfs,s_inode.ui_locationDataBlockNo[0]*VFS_BLOCKSIZE,SEEK_SET)) == -1){
              printf("ERROR: Cannot fetch the Data Block \n");
         }
         
         do{
              if((i_retVal=fread(&s_dientry,sizeof(struct directoryEntry),1,fpVfs)) != 1){
                   printf("ERROR: Cannot read the dientry block \n");
              }
              if(s_dientry.ui_inodeNo > 0){
                   currentNode = s_createNAryTreeNode(s_dientry.ui_inodeNo,fpVfs);
                   root = s_insertNAryTreeNode(root,currentNode);
              }       
              
         }while(s_dientry.ui_inodeNo != 0);
    }
 
    root = s_loadFileSystemAux(root, fpVfs);

    return root;
}


/*
Funtion Name: s_loadFileSystemAux
Description: The function helps in building the subtree of the n-Ary Tree which
             represents the file system mounted
Parameters: It takes two pointers.
            a) Pointer to a node in the n-Ary Tree
            b) File pointer to the file system to be loaded into the main memory.
Return Type: It returns a pointer which points to the root of the n-Ary subtree.
*/
struct nAryTreeNode * s_loadFileSystemAux(struct nAryTreeNode *nodePtr, FILE *fpVfs){

    struct nAryTreeNode *temp;
    struct nAryTreeNode *currentNode;

    struct directoryEntry s_dientry;

    int i_retVal = 0;

    temp = nodePtr;

    /* Move One Level Down */
    if(temp->leftChild != NULL){
         temp = temp->leftChild;
       
         while( (temp->s_inode->c_fileType[0] != 'd') && (temp->rightSibling != NULL) ){
              temp = temp->rightSibling;
         }
        
         if( (temp->rightSibling == NULL) && (temp->s_inode->c_fileType[0] != 'd') ){
              return temp->parent;
         }else{
         
              if(temp->s_inode->c_fileType[0] == 'd'){
                   if((fseek(fpVfs,temp->s_inode->ui_locationDataBlockNo[0]*VFS_BLOCKSIZE,SEEK_SET)) == -1){
                        printf("ERROR: Cannot fetch the Data Block \n");
                   }
         
                   do{
                        if((i_retVal=fread(&s_dientry,sizeof(struct directoryEntry),1,fpVfs)) != 1){
                             printf("ERROR: Cannot read the dientry block \n");
                        }
                        if(s_dientry.ui_inodeNo > 0){
                             currentNode = s_createNAryTreeNode(s_dientry.ui_inodeNo,fpVfs);
                             temp = s_insertNAryTreeNode(temp,currentNode);
                        }          
   
                   }while(s_dientry.ui_inodeNo != 0);
              }
              temp = s_loadFileSystemAux(temp,fpVfs);
         }
    }

    return nodePtr;
}

/*
Funtion Name: s_createNAryTreeNode
Description: It creates a node of the n-Ary Tree and loads the required data 
             into the node.
Parameters: It takes two parameters.
            a) Inode Number of the file system
            b) File pointer pointing to the file system to be loaded into the
               main memory.
Return Type:It returns a pointer, pointing to the node created.
*/
struct nAryTreeNode * s_createNAryTreeNode(int i_inodeNo,FILE *fpVfs){

    struct nAryTreeNode *temp;
    struct fileDescriptor s_inode;

    int i_retVal = 0;
    int i_tempInodeNo = 0;

    i_tempInodeNo = i_inodeNo;

    if((fseek(fpVfs,i_tempInodeNo*VFS_BLOCKSIZE,SEEK_SET)) == -1){
         printf("ERROR: Cannot fetch the Inode Block \n");
    }

    if((i_retVal=fread(&s_inode,sizeof(struct fileDescriptor),1,fpVfs)) != 1){
         printf("ERROR: Cannot read a Data Block \n");
    }

    /* 
      Code to Create a temp node here in n-Ary Tree 
    */
    temp = (struct nAryTreeNode *)malloc(sizeof(struct nAryTreeNode)*1);
    temp->s_inode = (struct fileDescriptor *)malloc(sizeof(struct fileDescriptor)*1);

    strcpy(temp->s_inode->cptr_fileName,s_inode.cptr_fileName);
    strcpy(temp->s_inode->cptr_filePath,s_inode.cptr_filePath);
    strcpy(temp->s_inode->c_fileType,s_inode.c_fileType);
    temp->s_inode->ui_inodeNo = s_inode.ui_inodeNo;
    temp->s_inode->ui_fileSize = s_inode.ui_fileSize;
    /* Modify this line of Code */
    temp->s_inode->ui_locationDataBlockNo[0] = s_inode.ui_locationDataBlockNo[0];
    temp->parent = NULL;
    temp->leftChild = NULL;
    temp->rightSibling = NULL;

    return temp;
}

/*
Funtion Name: s_insertNAryTreeNode
Description: It inserts a node into the n-Ary Tree.
Parameters: It takes two parameters
            a) A pointer pointing to the root of the n-Ary Tree
            b) A pointer pointing to the current node being inserted.
Return Type: It return a pointer, pointing to the root the n-Ary Tree
*/
struct nAryTreeNode * s_insertNAryTreeNode(struct nAryTreeNode *root,struct nAryTreeNode *currentNode){

    struct nAryTreeNode *temp;
    struct nAryTreeNode *tempParent;

    temp = tempParent = root;
    /* Base Case */
    if(NULL == root){
         root = currentNode;
    } else {

         if(NULL == temp->leftChild){
              temp->leftChild = currentNode;
              currentNode->parent = temp;
              currentNode->rightSibling = NULL;
         } else {
              tempParent = temp;
              temp = temp->leftChild;
              while(temp->rightSibling != NULL){
                   temp = temp->rightSibling;
              }
              temp->rightSibling = currentNode;
              currentNode->parent = tempParent;
              currentNode->rightSibling = NULL; 
         }

    }

    return root;
}
/*
Function Name: v_traverseNAryTree
Description: It traverses the n-Ary Tree from the node pointed by the pointer
             which is passed as a parameter.
Parameters : It takes a single parameter, which is the pointer to a particular
             node in the n-Ary Tree.
Return Type: It returns void
*/
void v_traverseNAryTree(struct nAryTreeNode *ptrToANode){
    struct nAryTreeNode *temp = NULL;

    temp = ptrToANode;

    if(NULL == temp){
         return;
    } else {
         v_traverseNAryTree(temp->leftChild);
#if DEBUG
    printf("DEBUG: FD No : %d \n",temp->s_inode->ui_inodeNo);
#endif
         v_traverseNAryTree(temp->rightSibling);
    }
}

/*
Function Name: s_searchNAryTreeNode
Description: It searches for a given file in the n-Ary Tree
Parameters: It takes 2 parameters
            1) Pointer to the root of the n-Ary Tree
            2) Name of the file to be searched in the n-Ary Tree
Return Type: It return a pointer to the node if the file is found in the
             n-Ary Tree else NULL
*/
struct nAryTreeNode *s_searchNAryTreeNode(struct nAryTreeNode *ptrToANode,char *cPtr_fileName){

    struct nAryTreeNode *temp = NULL;

    /* Assign temp to the root Node */
    temp = ptrToANode;

    if( NULL != temp ){
         if( (0 == strcmp(temp->s_inode->cptr_fileName,cPtr_fileName)) ){
              return temp;
         }
         s_searchNAryTreeNode(temp->leftChild,cPtr_fileName);
         s_searchNAryTreeNode(temp->rightSibling,cPtr_fileName);
    }

    return temp;
}

/*
Function Name: s_searchNAryTreeNode
Description: It searches for a given file in the n-Ary Tree
Parameters: It takes 2 parameters
            1) Pointer to the root of the n-Ary Tree
            2) Name of the file to be searched in the n-Ary Tree
Return Type: It return a pointer to the node if the file is found in the
             n-Ary Tree else NULL
*/
struct nAryTreeNode *s_searchInode_NAryTreeNode(struct nAryTreeNode *ptrToANode,unsigned int ui_inodeNo){

    struct nAryTreeNode *temp = NULL;

    /* Assign temp to the root Node */
    temp = ptrToANode;

    if( NULL != temp ){
         if( temp->s_inode->ui_inodeNo == ui_inodeNo ){
              return temp;
         }
         s_searchInode_NAryTreeNode(temp->leftChild,ui_inodeNo);
         s_searchInode_NAryTreeNode(temp->rightSibling,ui_inodeNo);
    }

    return temp;
}

/*
Function Name: s_getNAryTreeNode
Description: It creates a node of the type n-Ary Tree
Parameters: void
Return Type: It returns a pointers to the newly created n-Ary Tree Node
*/
struct nAryTreeNode *s_getNAryTreeNode(){

    struct nAryTreeNode *temp = NULL;

    temp = (struct nAryTreeNode *)malloc(sizeof(struct nAryTreeNode)*1);
    temp->s_inode = (struct fileDescriptor *)malloc(sizeof(struct fileDescriptor)*1);

    return temp;
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
void v_populateDataStructures(struct nAryTreeNode *root){

    struct nAryTreeNode *temp = NULL;

    temp = root;

    if(NULL == temp ){
         return;
    } else {
         v_populateDataStructures(temp->leftChild);
         /*insert(temp->s_inode);*/
         
              v_loadHashTable(temp->s_inode->ui_inodeNo,temp->s_inode->cptr_fileName);
         
         v_populateDataStructures(temp->rightSibling);
    }
}
