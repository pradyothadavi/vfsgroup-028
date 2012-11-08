#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bst.h"
#include "fileDescriptor.h"

struct node* bst_root=NULL;

void bst_inorder(struct node* root)
{
	struct node *temp;
	temp=root;
	if(temp!=NULL)
	{
		inorder(temp->lc);
		printf("%s\n",temp->bst_full_path);
		inorder(temp->rc);
	}
}

void bst_display(struct node* bst_root)
{
	if(bst_root==NULL)
	printf("empty tree\n");
	else
	{
	printf("root is %s\n",bst_root->bst_full_path);
	bst_inorder(bst_root);
	}
}

void bst_insert(struct fileDescriptor* s_inode)
{
	struct node* temp=NULL;
	struct node* root=bst_root;
	char fullPath[100];
		struct node* bst_new_node=(struct node*)malloc(sizeof(struct node));
		bst_new_node->lc=NULL;
		bst_new_node->rc=NULL;
		bst_new_node->parent=NULL;
		
		strcpy(fullPath,s_inode->cptr_filePath);
		if(strcmp(s_inode->cptr_filePath, "/")!=0)
		{
		strcat(fullPath,"/");
		strcat(fullPath,s_inode->cptr_fileName);
		}
		strcpy(bst_new_node->bst_full_path,fullPath);
		while(root!=NULL)
		{
			if(strcmp(fullPath,root->bst_full_path)<0)
			{
				temp=root;
				root=root->lc;
			}
			else
			if(strcmp(fullPath,root->bst_full_path)>0)
			{	
				temp=root;
				root=root->rc;
			}
			else
			{
				printf("file already exists\n");
				root=NULL;
			}
		}
				
			bst_new_node->parent=temp;

			if(temp==NULL)
				{
					bst_root=bst_new_node;
				}
			else if(strcmp(bst_new_node->bst_full_path,temp->bst_full_path)<0)
				{
					temp->lc=bst_new_node;
				}
			else
				temp->rc=bst_new_node;
			

}

struct node* bst_search(struct node* bst_root,struct fileDescriptor* full_Path)
{	
	
	struct node* temp=bst_root;
	char fullPath[100],filename[100];
   	strcpy(fullPath,full_Path->cptr_filePath);
	strcpy(filename,full_Path->cptr_fileName);
	strcat(fullPath,"/");
	strcat(fullPath,filename);
	if(temp==NULL)
		return temp;
	else

	{ 	
			if(strcmp(fullPath,temp->bst_full_path)<0)
				return bst_search(temp->lc,full_Path);
			if(strcmp(fullPath,temp->bst_full_path)>0)
		 		return bst_search(temp->rc,full_Path);
			if(strcmp(temp->bst_full_path,fullPath)==0)
				return temp;
			
		
	}
	
}

struct node* bst_min(struct node* root)
{
	struct node *temp=root;
	while(temp->lc!=NULL)
	{
	temp=temp->lc;
	}
	return temp;
}
	
void bst_transplant(struct node* t1, struct node* t2)
{	
	if(t1->parent==NULL)
	{
	bst_root=t2;
	}
	else {
		if (t1==t1->parent->lc)
		t1->parent->lc=t2;
		else 
		t1->parent->rc=t2;
	      }
	if(t2!=NULL)
	t2->parent=t1->parent;
}

void bst_delete(struct fileDescriptor* fullPath)
{	
	struct node* loc=(struct node*)malloc(sizeof(struct node));
	loc=bst_search(bst_root,fullPath);
	if(loc!=NULL)
	{
		if(loc->lc==NULL)
		{
		bst_transplant(loc,loc->rc); 
		}
		else 
			{
			if(loc->rc==NULL)
			bst_transplant(loc,loc->lc);
			else 
			{
				struct node * loc1=bst_min(loc->rc);
		 		if(loc1->parent!=loc)
				{
				bst_transplant(loc1,loc1->rc);
				loc1->rc=loc->rc;
				loc1->rc->parent=loc1;
				}
				bst_transplant(loc,loc1);
				loc1->lc=loc->lc;
				loc1->lc->parent=loc1;
				loc1->parent=loc->parent;
			}
		}	
		free(loc);
	}
	else
	printf("element to be deleted not present\n");
	
}		
	


		




