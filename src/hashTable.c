#include "hashTable.h"

/*
Function Name: v_initializeHashTable
Description: It initializes the hash table with the required parameters
Parameters: It does not take any parameters
Return Type: It returns void
*/
void v_initializeHashTable(){
		int j;
		for(j=0;j<26;j++){
		hashTable[j]=(struct chain *)malloc(sizeof(struct chain)*1);
		hashTable[j]->next=NULL;
		
		}
}

/*
Function Name: v_loadHashTable
Description: It loads the hash table with all the files in the file system using
             the hash function.
Parameters: It takes inode number and fileName as input
Return Type: It return's void
*/
void v_loadHashTable(unsigned int inode,char[] fileArray){

	int index=calculateIndex(fileArray);
	struct chain *newNode;
	
        struct chain *temp;
	
	if(hashTable[index]->next==NULL){
	
		newNode=(struct chain*)malloc(sizeof(struct chain));
		strcpy(newNode->c_fileName,fileArray);
		newNode->i_inodeNo=iNode;
		newNode->next=NULL;	
	
		hashTable[index]->next=newNode;

	}
	else if (hashTable[index]->next!=NULL){
		
		newNode=(struct chain*)malloc(sizeof(struct chain));
		strcpy(newNode->c_fileName,fileArray);
		newNode->i_inodeNo=iNode;
                newNode->next=NULL;
		
		temp=hashTable[index]->next;
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=newNode;
		
		
	}
    

                  /*1. Fetch the file name and inode number

                  2. Calculate the index

                  3. Insert into hash table (insert module)
                       i) two parameters index, file name*/
}

int calculateIndex(char[] fileArray){
			char *fileName;
			fileName=fileArray;
			firstChar=*fileName;
			index=toascii(firstChar)-97;
			//insertFile(hashTable,index-97,fileArray);	
}



/*
Function Name: l_searchHashTable
Description: It searches the hashTable based on the fileName only
Parameters: It takes fileName as parameter
Return Type: It returns a linked list of files with the name to be searched
*/

struct chain* searchHashTable(char fileArray[]){
	int index=calculateIndex(fileArray);

	struct chain *p=hashTable[index]->next;
	struct chain *head=(struct chain*)malloc(sizeof(struct chain));
	struct chain *newNode;
	head->next=NULL;
	head=NULL;
	int i;
	if(hashTable[index]->next->c_fileName==NULL){
		printf("File not found !!! \n");	
		
		return head;
	}
	else{
		
		while(p!=NULL){
		
			i=strcmp(p->c_fileName,fileArray);
			if(i==0){

				newNode=(struct chain*)malloc(sizeof(struct chain));
				strcpy(newNode->c_fileName,fileArray);
				if(head==NULL){	
					head=newNode;
					
				}
				else{

					newNode->next=head;
				}	head=newNode;
				p=p->next;
				
			}
			else
				p=p->next;
		}
	return head;
	}	
}

/*
Function Name: v_delete
Description: It deletes a fileName from hashTable base on unique iNode number and fileName
Parameters: It takes fileName and inode number as parameter
Return Type: It does not return anything
*/


void v_delete(int iNode,char fileArray[]){

	int index=calculateIndex(fileArray);
	int j;
	
	struct chain *start=hashTable[index]->next;
	struct chain *previous=hashTable[index];
	if(hashTable[index]->next->c_fileName==NULL){
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

