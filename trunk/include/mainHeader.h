#ifndef _MAIN_HEADER_
#define _MAIN_HEADER_

/*
Group No : 28
Version No : 1.0
*/

/* This header file has the datatype definitions used for the main header */

#include "fileSystemOps.h"

struct mainHeader{
    char c_fileSystemLabel[VFS_NAMELEN];
    unsigned int ui_uniqueNo;
    unsigned int ui_maxNoOfFileDescriptors;
    unsigned int ui_noOfUsedFileDescriptors;
    unsigned int ui_totalBlocks;
    unsigned int ui_startBlockNoOfInodeArray;
    unsigned int ui_startBlockNoOfDataBlockArray;
};

#endif 
