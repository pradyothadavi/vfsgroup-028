#include"mainHeader.h"
#include"nAryTree.h"
#include"fileDescriptor.h"
#include"block.h"
#include<global.h>
#include<string.h>
#include "limits.h"
#include "fileSystemOps.h"
/*
Function Name: listfile
Description: It traverses the nary search Tree from the root with the entire path passed as parameter to get the file descriptor
Parameters : It takes two parameters, file path from VFS and external file path
Return Type: It returns void
*/

void v_listfile (char *P1 ,char *P2){
	
	struct nAryTreeNode *nary= NULL;
	struct dataBlock bufferBlock;
	char *vfsLabel;
	FILE *f;
	int i_count;
	static int i_noOfCharacters;	
	char *token;
	char *ndir= NULL;
	FILE *fpVfs;

	ndir=P1;
	vfsLabel="demo";
	nary=sPtr_rootNAryTree;
	fpVfs=fopen(vfsLabel,"r");
	token=strtok(ndir,"/");
             while(token!=NULL)
             {  
                 
             i_noOfCharacters=strlen(token)+1;
             nary=s_searchNAryTreeNode(nary,token);

              if(NULL==nary)
                 {   
                     printf(ERR_VFS_LISTFILE_01);
                                     
                 }
                 
               token=strtok(NULL,"/");
            }
	
	
/* Moving the file pointer of the file system to the free data block */
            if((fseek(fpVfs,(long)nary->s_inode->ui_locationDataBlockNo[0]*VFS_BLOCKSIZE,SEEK_SET)) == -1){
           printf("ERROR: cannot reach to the free block \n");
            printf("STATUS: Program Terminated \n");
         }
/* Initializing the contents of buffer to zero */
         memset((void *)&bufferBlock,0,VFS_BLOCKSIZE);
/* reading the 1024 bytes each time from file and writing to the buffer */        
        if((i_count=fread(&bufferBlock,sizeof(struct dataBlock),1,fpVfs)) != 1){
              printf("DEBUG: error in reading the file \n");
         }
	f=fopen(P2,"w");
	 if((i_count=fwrite(&bufferBlock,sizeof(struct dataBlock),1,f)) != 1){
         printf("ERROR: could not write the file contents to the data block \n");
        }
	fclose(f);
	fclose(fpVfs);
}





