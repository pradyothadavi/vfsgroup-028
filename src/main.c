#include <stdio.h>
#include "limits.h"
#include "fileSystemOps.h"

int main(int argc, char *argv[]){

#if DEBUG
    printf("DEBUG: Test OK! \n");
#endif

    create_vfs("/home/pradyot/firstVfs.dat",10240000);

    mount_vfs("/home/pradyot/firstVfs.dat");

    return 0;
}
