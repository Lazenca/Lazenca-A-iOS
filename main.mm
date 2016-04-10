#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/sysctl.h>
#import <Foundation/Foundation.h>
#import "MemoryCheat.h"
#import "RunningProces.h"
#import "Process.h"
#import "Write.h"
#import "Util.h"

#ifdef __LP64__
#import "Map_64.h"
#import "MemRead_64.h"
#else
#import "Map.h"
#import "MemRead.h"
#endif

int main(int argc, char **argv, char **envp) {
    char cmd[BUFSIZE];
    
    @autoreleasepool {
        while (1) {
            printf("%s",COMMAND);
            scanf("%29[^\n]s",cmd);
            getchar();
            
            char command1[BUFSIZE] = {'\0',};
            char command2[BUFSIZE] = {'\0',};
            char command3[BUFSIZE] = {'\0',};
            sscanf(cmd,"%s%s%s", command1, command2, command3);
            printf("%s %s %s\n",command1, command2, command3);
            
            //Process List Print
            if (!strcmp(PROCESS,strupr(command1))) {
                 ProcessList();
            //Process Attach
            }else if(!strcmp(ATTACH,strupr(command1))){
                //sscanf(command2,"%d",&pid);
                pid = atoi(command2);
                setPid();
                findWriteableRegions();
            //Value Search
            }else if (!strcmp(SEARCH,strupr(command1))) {
                printf("%s, %s\n",strupr(command1),command2);
                
                long value;
                sscanf(command2,"%ld",&value);
                SearchProcess(value);
            //Pick
            }else if (!strcmp(PICK,strupr(command1))) {
                printf("%s, %s\n",strupr(command1),command2);
                
                long value;
                sscanf(command2,"%ld",&value);
                getValueAddress(value);
            //Write
            }else if(!strcmp(WRITE,strupr(command1))){
                long address, value;
                sscanf(command2,"%ld",&address);
                sscanf(command3,"%ld",&value);
                MemoryWrite(address,value);
            //Find data list
            }else if(!strcmp(SHOWLIST,strupr(command1))){
                showDataList();
            //Clear data list
            }else if(!strcmp(CLEAR,strupr(command1))){
                MemoryClear();
            }else if(!strcmp(EXIT,strupr(command1))){
                exit(0);
            }
        }
    }
    return 0;
}