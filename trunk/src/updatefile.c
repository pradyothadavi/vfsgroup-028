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
void v_updatefile ( char *P1, char *P2 )
{
/* P2 is source file path from hard disk with file name and P1 is the destination file path */
 
    struct nAryTreeNode *nary= NULL,*nary1=NULL;
    struct nAryTreeNode *temp= NULL;
    struct dataBlock bufferBlock;
    struct fileDescriptor s_newinode;
    struct nAryTreeNode *newNode;
    struct fileDescriptor *s_inode; 
    FILE *fpVfs,*fp,*f;

  
     int i_tempinodeNo,i_tempdatablockno;  
     int i_count;
     int i_noOfBlocks;
     int long size;
     static int i_noOfCharacters;
     int i=0;
     
     char *token;
     char *ndir= NULL,*ndir1=NULL;
     char *parentPath;
     char *result;
	char *cptr_tempfilename,*cptr_tempfilepath;
        nary=sPtr_rootNAryTree;
	nary1=sPtr_rootNAryTree;
       ndir=P1;
	ndir1=P1;     
 
/* Validating the destination directory path given and also creating directory in the process if it does not exist */
             token=strtok(ndir,"/");
             while(token!=NULL)
             {  
                 
             i_noOfCharacters=strlen(token)+1;
             nary=s_searchNAryTreeNode(nary,token,NONRECURSIVE);

              if(NULL==nary)
                 {   
                     strncpy(parentPath,P1,i_noOfCharacters);
                     strcpy(parentPath,"/0");
		     makedir (parentPath,token);      
                     nary=s_searchNAryTreeNode(nary,token,NONRECURSIVE);
                                     
                    }
                 
               token=strtok(NULL,"/");
 

          }
	
                                       

/* creating a temporary file */
if((fp=fopen("../test/temp.txt","a+"))==NULL);
printf("error in opening temporary file");

/* Opening the file System in the write mode*/
if((fpVfs = fopen("demo","wb+")) == NULL){                                         /*check*/
 	        printf("ERROR: Cannot Open the File System \n");
 	        printf("STATUS: Program Terminated \n");
 	        exit(1);
 		   }



/*tokenizing the destination file path to get the file name and its locationdata block no*/
	
  result=strtok(ndir1,"/");
             while(result!=NULL)
             {  
                 
		nary1=s_searchNAryTreeNode(nary1,result,NONRECURSIVE);

              if(NULL==nary1)
                 {   
                     printf("dsetination file path not found");
                                     
                    }
                 
               token=strtok(NULL,"/");
            }


	i_tempinodeNo=nary1->s_inode->ui_inodeNo;
	i_tempdatablockno=nary1->s_inode->ui_locationDataBlockNo[0];
	strcpy(cptr_tempfilename,nary1->s_inode->cptr_fileName);
	strcpy(cptr_tempfilepath,nary1->s_inode->cptr_filePath);


/*opening the destination file to copy the data into buffer*/
if((fpVfs = fopen(P1,"r")) == NULL){                                         /*check*/
 	        printf("ERROR: Cannot Open the destination file\n");
 	        printf("STATUS: Program Terminated \n");
 	        exit(1);
 		   }

 if((fseek(fpVfs,(long)i_tempdatablockno*VFS_BLOCKSIZE,SEEK_SET)) == -1){
           printf("ERROR: cannot reach to the free block \n");
            printf("STATUS: Program Terminated \n");
         exit(1);
                }
/* Initializing the contents of buffer to zero */
         memset((void *)&bufferBlock,0,VFS_BLOCKSIZE);

/* reading the 1024 bytes each time from file and writing to the buffer */        
        if((i_count=fread(&bufferBlock,sizeof(struct dataBlock),1,fpVfs)) != 1){
              printf("DEBUG: error in reading the file \n");
         }

 /* Writing the buffer contents to the temporary file in the file system*/        
       if((i_count=fwrite(&bufferBlock,sizeof(struct dataBlock),1,fp)) != 1){
         printf("ERROR: could not write the file contents to the temporary file \n");
        }
      

else         
           printf("ERROR:file cannot be opened \n");


	/*deleting that file from the nary tree*/
	removefile(P1);

   
/* Opening the source file  */
	
      f = fopen(P2,"r");  
       if(f!=NULL)
{
        if((fseek(f,0,SEEK_END))==-1){
         printf("ERROR: error in reading file \n");
          return;
    }                                
 }	       

/* reading the 1024 bytes each time from file and writing to the buffer */        
        if((i_count=fread(&bufferBlock,sizeof(struct dataBlock),1,f)) != 1){
              printf("DEBUG: error in reading the file \n");
         }

/* Writing the buffer contents to the temporary file in the file system*/        
       if((i_count=fwrite(&bufferBlock,sizeof(struct dataBlock),1,fp)) != 1){
         printf("ERROR: could not write the buffer content to the temporary file \n");

}
    
  /* Calculating the size of the file to be written into the file system   */ 
           if(fp!=NULL)
{
        if((fseek(fp,0,SEEK_END))==-1){
         printf("ERROR: error in reading file \n");
         printf("STATUS: Files size can not be obtained \n");
         return;
    }
        
         size=ftell(fp);
         fclose(fp);
         printf("%ld\n",size);
         if(size<=1024)
         i_noOfBlocks=1;

   /* Calculating the number of data blocks required to write file into the file system */
        else 
           {
            printf("ERROR:exceeded size");
            return;
            }
	}
v_addfile ( cptr_tempfilepath,cptr_tempfilename,"../test/temp.txt");

 }
