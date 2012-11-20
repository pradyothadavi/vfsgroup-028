#include<string.h>
#include<stdio.h>
#include "freeList.h"
#include "fileSystemOps.h"
#include "fileDescriptor.h"
#include "mainHeader.h"
#include "block.h"
#include "nAryTree.h"
#include "global.h"
#include "freeList.h"
void v_movefile ( char *P1, char *P2)
{
  /* P1 is source file path with file name and P2 is the destination file path */
    struct nAryTreeNode *narysource= NULL;
    struct nAryTreeNode *narydest= NULL;
    
   
    struct fileDescriptor s_newinode;
    struct nAryTreeNode *newNode;
     
    FILE *fpVfs = NULL;
	int i_inodeNo,i_retVal;
  
    
    
     static int i_noOfCharacters;

      

     char *token;
     char *sourcePath= NULL;
     char *destinationPath= NULL;
     char *parentPath;
       narysource=sPtr_rootNAryTree;
       narydest=sPtr_rootNAryTree;
       sourcePath=P1;
       destinationPath=P2;

/*validating the source path */
  token=strtok(sourcePath,"/");
             while(token!=NULL)
             {  
                 
            
             narysource=s_searchNAryTreeNode(narysource,token,NONRECURSIVE);

              if(NULL==narysource)
                 {   
                    printf("\nERROR: Invalid Source Path\n");
                     return;                
                    }
                 
               token=strtok(NULL,"/");
            }	







/* Validating the destination directory path given and also creating directory in the process if it does not exist */
             token=strtok (destinationPath,"/");
             while(token!=NULL)
             {  
                 
             i_noOfCharacters=strlen(token)+1;
             narydest=s_searchNAryTreeNode(narydest,token,NONRECURSIVE);

              if(NULL==narydest)
                 {   
                     strncpy(parentPath,P1,i_noOfCharacters);
                     strcpy(parentPath,"/0");
		     makedir (parentPath,token);      
                     narydest=s_searchNAryTreeNode(narydest,token,NONRECURSIVE);
                                     
                    }
                 
               token=strtok(NULL,"/");
            }
 

       i_inodeNo= narysource->s_inode->ui_inodeNo;
  
       /* Initializing the parameters of the  file descriptors*/   
          memset((void *)&s_newinode,0,sizeof(struct fileDescriptor));
          strcpy(s_newinode.cptr_fileName,narysource->s_inode->cptr_fileName);
          strcpy(s_newinode.cptr_filePath,P2);
          s_newinode.c_fileType[0]='r';
          s_newinode.c_fileType[1]='\0';
         
          s_newinode.ui_fileSize =narysource->s_inode->ui_fileSize ;
        
  
          s_newinode.ui_inodeNo = i_inodeNo ;
          s_newinode.ui_locationDataBlockNo[0]=narysource->s_inode->ui_locationDataBlockNo[0];





/* Opening the file System in the write mode to write the filePath to the existing file filedescriptor block*/
 	if((fpVfs = fopen("demo","wb+")) == NULL){                                         /*check*/
 	        printf("ERROR: Cannot Open the File System \n");
 	        printf("STATUS: Program Terminated \n");
 	        exit(1);
 		   }
/* writing the file path  to the existing file filedescriptor block in the file system  */
 if((fseek(fpVfs,i_inodeNo*VFS_BLOCKSIZE,SEEK_SET))==-1){
         printf("ERROR: Error In Creating Root Inode \n");
         printf("STATUS: Root Directory Could Not Initialized \n");
    }

    if((i_retVal=fwrite(&s_newinode,sizeof(struct fileDescriptor),1,fpVfs)) != 1){
         printf("ERROR: Could not write the '/' information to the data block \n");  

    }

     removefile(P1);
     newNode=s_createNAryTreeNode(i_inodeNo,fpVfs);
     
     sPtr_rootNAryTree=s_insertNAryTreeNode(narydest,newNode);
     
      } 
  
    
