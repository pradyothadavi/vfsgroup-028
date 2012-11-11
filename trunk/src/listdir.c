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
void listdir(char *p1, char *p2,char *p3)
{

    struct nAryTreeNode *nary= NULL;
    
    struct nAryTreeNode *temp= NULL;
    struct nAryTreeNode *ntemp;
    struct chain *listptr;
    struct chain *temp1;
    struct chain *head;

    char *ndir= NULL;
    char *token=NULL;
    char *n;
    int nodeNO;
    listptr=(struct chain*)malloc(sizeof(struct chain));
    head=(struct chain*)malloc(sizeof(struct chain));
    listptr=NULL;
    
    int nodeNO;
       nary=sPtr_rootNAryTree;
       ndir=p1;
/*      */ 
	if(strcmp(p2,0)==0)
          {
             token=strtok(ndir,"/");
             while(token!=NULL)
             {  
  
	     
              nary=s_searchNAryTreeNode(nary,token);

              if(NULL==nary)
                 {
			printf("cannot print");
                  	return;

		}
              token=strtok(NULL,"/");
                 }
                if(NULL!=nary)
		print_NonRecursive(nary);
           
                }
      else
          
	  {
            
             do
                {
 


                     token=strtok(ndir,"/");
                     while(token!=NULL)
                      {  
  
	     
                          nary=s_searchNAryTreeNode(nary,token);

                             if(NULL==nary)
                               {
		                 	printf("cannot print");
                  	                return;

		               }
                            token=strtok(NULL,"/");
                       }
                    if(NULL!=nary)
                   ntemp=nary;
                   
               do{
                    listptr=print_Recursive(ntemp,listptr);
                    n=listptr->c_fileName;
                    ntemp=s_searchNAryTreeNode(nary,n);
                     temp1=listptr;
                    listptr=listptr->next;
                    free(temp1);
                    }while(listptr!=NULL);
                }while(nary!=NULL);

         }

 void  print_NonRecursive(struct nAryTreeNode *nary)
{

           struct nAryTreeNode *temp= NULL;
           temp=nary;
	   temp=temp->leftChild;
           do
	     {
		
          
           	printf("%s/t",temp->s_inode->cptr_fileName);
           	temp=temp->rightSibling;
              }while(temp!=NULL);


}


   struct *chain print_Recursive(struct nAryTreeNode *nary, struct chain *head)
       {
        
         struct nAryTreeNode *temp= NULL;
         temp=nary;
         struct *chain head,list,ltemp;
         list=head;
         
         do 
	    {
		temp=temp->leftChild;
	        printf("%s/t",temp->s_inode->cptr_fileName);
                if(temp->s_inode->cptr_fileType[0]='d')
                 {
                   list=(struct chain*)malloc(sizeof(struct chain));
                   strcpy(list->c_fileName,temp->s_inode->cptr_fileName);
                   list->i_inodeNo=temp->s_inode->ui_inodeNo;
                   list->next=NULL;

                  if(head==NULL)
                    {
                       
                      
                      head=list;
                   }


                  else
		    {
                      ltemp=head;
                      while(ltemp->next!=NULL)
			{
			   ltemp=ltemp->next;
                        }
		
		      ltemp->next=list;                 

                    
                    }
              }

               temp=temp->rightSibling;

        }while(temp!=NULL);

  return head;            
}



