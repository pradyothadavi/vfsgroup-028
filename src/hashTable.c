
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

#include "hashTable.h"
#include "global.h"

struct chain *hashTableBucket[26];

/*
Function Name: v_initializeHashTable
Description: It initializes the hash table with the required parameters
Parameters: It does not take any parameters
Return Type: It returns void
*/
void v_initializeHashTable(){
		int j;
		for(j=0;j<26;j++){
		hashTableBucket[j]=(struct chain *)malloc(sizeof(struct chain)*1);
		hashTableBucket[j]->next=NULL;
		
		}
}

/*
Function Name: v_loadHashTable
Description: It loads the hash table with all the files in the file system using
             the hash function.
Parameters: It takes inode number and fileName as input
Return Type: It return's void
*/
void v_loadHashTable(unsigned int iNode,char fileArray[]){

	int index=0;
	struct chain *newNode;
	
        struct chain *temp;
	index=i_calculateIndex(fileArray);
	
	
	if(hashTableBucket[index]->next==NULL){
	
		newNode=(struct chain*)malloc(sizeof(struct chain));
		strcpy(newNode->c_fileName,fileArray);
		newNode->i_inodeNo=iNode;
		newNode->next=NULL;	
	
		hashTableBucket[index]->next=newNode;

	}
	else if (hashTableBucket[index]->next!=NULL){
		
		newNode=(struct chain*)malloc(sizeof(struct chain));
		strcpy(newNode->c_fileName,fileArray);
		newNode->i_inodeNo=iNode;
                newNode->next=NULL;
		
		temp=hashTableBucket[index]->next;
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=newNode;
		
		
	}
    

                  /*1. Fetch the file name and inode number

                  2. Calculate the index

                  3. Insert into hash table (insert module)
                       i) two parameters index, file name*/
}

int i_calculateIndex(char fileArray[]){
			char *fileName;
			char firstChar;
			int index=0;
			fileName=fileArray;
			firstChar=*fileName;
			index=toascii(firstChar);
			index=index-97;
			return index;
				
}



/*
Function Name: searchHashTable
Description: It searches the hashTable based on the fileName only
Parameters: It takes fileName as parameter
Return Type: It returns a linked list of files with the name to be searched
*/

struct chain* searchHashTable(char fileArray[]){
	int index=i_calculateIndex(fileArray);
	int i=1,j=0;
	struct chain *p=hashTableBucket[index]->next;
	struct chain *head=(struct chain*)malloc(sizeof(struct chain));

	head->next=NULL;
	head=NULL;
	
	if(hashTableBucket[index]->next->c_fileName==NULL){
		printf("File not found !!! \n");	
		
		return head;
	}
	else{
		
		
		while(p!=NULL){
			for(j=0;j<strlen(fileArray);j++){
				if(fileArray[j]!=p->c_fileName[j]){
					i=0;
					break;
				}
       				else{
					i=1;
				} 
			}
			if(i==1){
				
				head=addToList(head,p->c_fileName);
				p=p->next;
				
			}
			else
				p=p->next;
		}

	return head;
	}	
		
}
/*
Function Name: addToList
Description: It adds the file to the linked list that has matched the prefix
Parameters: It takes head of linked list and fileName as input
Return Type: It returns a linked list of files with the prefix to be searched to search module
*/

struct chain *addToList(struct chain *head,char fileArray[]){
	struct chain *newNode;
	newNode=(struct chain*)malloc(sizeof(struct chain));
	strcpy(newNode->c_fileName,fileArray);
	if(head==NULL){	
			head=newNode;
					
	}
	else{

		newNode->next=head;
		head=newNode;
	}
	return head;
}


/*
Function Name: v_delete
Description: It deletes a fileName from hashTable base on unique iNode number and fileName
Parameters: It takes fileName and inode number as parameter
Return Type: It does not return anything
*/


void v_delete(int iNode,char fileArray[]){

	int index=i_calculateIndex(fileArray);
	int j;
	
	struct chain *start=hashTableBucket[index]->next;
	struct chain *previous=hashTableBucket[index];
	if(hashTableBucket[index]->next->c_fileName==NULL){
		printf("No file with this name!!!\n");
		return;
	}

	

	else{
		
		while(start!=NULL){
			j=strcmp(start->c_fileName,fileArray);
			if(j==0 && start->i_inodeNo==iNode){
				if(start->next==NULL){
					previous->next=NULL;
					free(start);
					return;
				}
				else{
				previous->next=start->next;
				free(start);
				return;
				}
			}
			else{
				start=start->next;
				previous=previous->next;
			}
		}
	
	
	}
}

