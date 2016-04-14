#include <vector>
#include <mach/mach.h>


/*
 * Command Input
 */
#define BUFSIZE 30
#define COMMAND "Lazenca A : "

#define MEMREADSIZE 4096

/*
 * http
 */
#define	MAX_PATH		260
#define	BUFF_MAX		0x2000

/*
 * Command
 */
#define SEARCH "SEARCH"
#define FUZZING "FUZZING"
#define WRITE "WRITE"
#define PROCESS "PROCESS"
#define ATTACH "ATTACH"
#define CONTROL "CONTROL"
#define SHOWLIST "SHOWLIST"
#define THREADLIST "THREADLIST"
#define CONTROL "CONTROL"
#define PICK "PICK"
#define CLEAR "CLEAR"
#define ENABLE "ENABLE"
#define DISABLE "DISABLE"
#define EXIT "EXIT"

/*
 * Fuzzing Option
 */
#define SMALLER "SMALLER"
#define LAGER "LAGER"
#define EQUAL "EQUAL"
#define NOTEQUAL "NOTEQUAL"

/*
 * Attach
 */
pid_t pid;
mach_port_name_t target_task;
mach_port_name_t tmp_target_task;

#ifdef __LP64__
typedef struct REGION{
    vm_address_t startAddr;
    vm_address_t endAddr;
    vm_size_t size;
}INFOREGION;

typedef struct ADDRDATAPAIR{
    vm_address_t address;
    long value;
}INFODATA;


std::vector<INFOREGION> regionList;
INFOREGION regionStruct;


std::vector<INFODATA> findDataList;
INFODATA findInfoStruct;


std::vector<INFODATA> tempDataList;
INFODATA tempInfoStruct;


std::vector<INFODATA> lockDatalist;
INFODATA lockDataStruct;


std::vector<INFODATA> memDataList;
INFODATA memInfoStruct;

#else
typedef struct REGION{
    vm_address_t startAddr;
    vm_address_t endAddr;
    vm_size_t size;
}INFOREGION;

typedef struct{
    vm_address_t address;
    double value;
}INFODATA;


std::vector<INFOREGION> regionList;
INFOREGION regionStruct;


std::vector<INFODATA> findDataList;

std::vector<INFODATA> tempDataList;
INFODATA findInfoStruct;


std::vector<INFODATA> lockDatalist;
INFODATA lockDataStruct;


std::vector<INFODATA> memDataList;
INFODATA memInfoStruct;
#endif

long long searchRange = 0x200000000;

int isCMDRUNNING = 0;

char errorMsgCmdErr[MAX_PATH] = "Error : input!";

#include <ctype.h>
char *strupr(char*);

char *strupr(char *s) {
    char *p = s;
    
    while (*p) {
        *p = (char) toupper(*p);
        p++;
    }
    return s;
}

void showDataList(){
    if(findDataList.size() != 0){
        for (int i = 0; i < findDataList.size(); i++) {
            
            findInfoStruct = findDataList.at(i);
#ifdef __LP64__
            printf("Address : %lx , Address(long) : %lu, Value : %ld\n",findInfoStruct.address,findInfoStruct.address,findInfoStruct.value);
#else
            printf("Address : %x , Address(long) : %u, Value : %f\n",findInfoStruct.address,findInfoStruct.address,findInfoStruct.value);
#endif
        }
        printf("Total Count : %lu\n",findDataList.size());
        
    }else{
        printf("size 0!\n");
    }
}

void MemoryClear(){
    findDataList.clear();
    memDataList.clear();
    lockDatalist.clear();
    isCMDRUNNING = 0;
}

int chkFuzzingCommand(char *s){
    if(!strcmp( SMALLER, strupr(s))){
        return 1;
    }
    if(!strcmp( LAGER, strupr(s))){
        return 1;
    }
    if(!strcmp( EQUAL, strupr(s))){
        return 1;
    }
    if(!strcmp( NOTEQUAL, strupr(s))){
        return 1;
    }
    printf("%s\n",errorMsgCmdErr);
    return 0;
}

