#include <stdio.h>
#include <string.h>
#include "nAryTree.h"
#include "directoryOps.h"

/*
Function Name:
Description:
Parameters:
Return Type:
*/
void v_makedir(char *cPtr_directoryPath,char *cPtr_directoryName){

    struct nAryTreeNode *currentNode = NULL;
   
    char *cPtr_token = NULL;

    /* Tokenize the directory path */
    cPtr_token = strtok(cPtr_directoryPath,"/");
    while(cPtr_token != NULL){
         currentNode = s_searchNAryTreeNode(struct nAryTreeNode *,char *)
    }    
}
