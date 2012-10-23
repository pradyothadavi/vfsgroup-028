#ifndef _BST_
#define _BST_

/*
Group No : 28
Version No : 1.0
*/

/* This header file has the datatype definitions for the BST */

#include "fileDescriptor.h"

typedef struct node{
	struct fileDescriptor *s_inode;
	char bst_full_path[50];
	struct node *lc;
	struct node *rc;
	struct node *parent;
}bst_node;
struct node *bst_root=NULL;

void insert(struct fileDescriptor* );

void inorder(struct node* );

void display(struct node* );

struct node* search(struct node* ,struct fileDescriptor* );

struct node* min(struct node* );

void transplant(struct node* , struct node* );

void delete(struct node* ,struct fileDescriptor* );
#endif	
