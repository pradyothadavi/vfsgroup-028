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
void movefile ( char *P1, char *P2)
{
  /* P2 is source file path from hard disk with file name and P1 is the destination file path */
   
    struct nAryTreeNode *narydest= NULL;
    struct nAryTreeNode *temp= NULL;
    struct dataBlock bufferBlock;
   
    struct fileDescriptor s_newinode;
    struct nAryTreeNode *newNode;
     
    FILE *fpVfs = NULL;
    int i=0;
    
  
    
    
     static int i_noOfCharacters;

      

     char *token;
     char *sourcePath= NULL;
     char *destinationPath= NULL;
     char *parentPath;
      
       narydest=sPtr_rootNAryTree;
       sourcePath=P2;
       destinationPath=P1;



/* Validating the destination file path given and also creating directory in the process if it does not exist */
             token=strtok(ndirdest,"/");
             while(token!=NULL)
             {  
                 
             i_noOfCharacters=strlen(token)+1;
             narydest=s_searchNAryTreeNode(narydest,token);

              if(NULL==narydest)
                 {   
                     strncpy(parentPath,P1,i_noOfCharacters);
                     strcpy(parentPath,"/0");
		     makedir (parentPath,token);      
                     narydest=s_searchNAryTreeNode(narydest,token);
                                     
                    }
                 
               token=strtok(NULL,"/");
            }
 
  i_inodeNo=narydest->s_inode->ui_inodeNo;


 /* Calculating the size of the file to be wriiten into the file system   */ 
       FILE *f=fopen(P2,"r");
       if(f!=NULL)
{
        if((fseek(f,0,SEEK_END))==-1){
         printf("ERROR: error in reading file \n");
         printf("STATUS: Files size can not be obtained \n");
         return;
    }
        
         size=ftell(f);
         fclose(f);
   /* Calculating the number of data blocks required to write file into the file system */
         i_noOfBlocks= size/1024;

   
     
   /* Initializing the parameters of the file descriptors  */   
          memset((void *)&s_newinode,0,sizeof(struct fileDescriptor));
          strcpy(s_newinode.cptr_fileName,P2);
          strcpy(s_newinode.cptr_filePath,P1);
          s_newinode.c_fileType[0]='r';
          s_newinode.c_fileType[1]='\0';
         
          s_newinode.ui_fileSize = size;
        
  
          s_newinode.ui_inodeNo = i_inodeNo ;
          s_newinode.locationDataBlock[0]=narydest->s_inode->ui_locationDataBlockNo[0];    
    
    
 }
else
{         
           printf("ERROR:file cannot be opened \n");

}


  if((f=fopen(P2,"r"))!=NULL)
     {
	FILE *fpVfs;
/* Opening the file System in the write mode to write the contents to the free data block*/
 	if((fpVfs = fopen(vfsLabel,"wb+")) == NULL){                                         /*check*/
 	        printf("ERROR: Cannot Open the File System \n");
 	        printf("STATUS: Program Terminated \n");
 	        exit(1);
 		   }
/* writing the file descriptors to the free block in the file system  */
 if((fseek(fpVfs,i_inodeNo*VFS_BLOCKSIZE,SEEK_SET))==-1){
         printf("ERROR: Error In Creating Root Inode \n");
         printf("STATUS: Root Directory Could Not Initialized \n");
    }

    if((i_retVal=fwrite(&s_newinode,sizeof(struct fileDescriptor),1,fpVfs)) != 1){
         printf("ERROR: Could not write the '/' information to the data block \n");
    }
/* Moving the file pointer of the file system to the free data block */
             i_noOfBlocks=size/1024;
       while(i_noOfBlocks!=0)
       {
            if((fseek(fpVfs,(long)s_newinode.ui_locationDataBlockNo[i]*VFS_BLOCKSIZE,SEEK_SET)) == -1){
           printf("ERROR: cannot reach to the free block \n");
            printf("STATUS: Program Terminated \n");
         exit(1);
                 }
/* Initializing the contents of buffer to zero */
         memset((void *)&bufferBlock,0,VFS_BLOCKSIZE);
/* reading the 1024 bytes each time from file and writing to the buffer */        
        if((i_count=fread(&bufferBlock,sizeof(struct dataBlock),1,f)) != 1){
              printf("DEBUG: error in reading the file \n");
         }
 /* Writing the buffer contents to the data block in the file system*/        
       if((i_count=fwrite(&bufferBlock,sizeof(struct dataBlock),1,fpVfs)) != 1){
         printf("ERROR: could not write the file contents to the data block \n");
        }
       i++;
       i_noOfBlocks--;
    

      } 

        }  

else 
     {         
           printf("ERROR:file cannot be opened \n");

      }






