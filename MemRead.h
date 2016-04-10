#include <vector>
#import "Util.h"
#import "process.h"

void getValueArea(vm_address_t startAddress,vm_address_t endAddress, void* buffer,long number){
    
    kern_return_t result;
    
    long readArea = 0;
    vm_size_t outsize;
    
    while(endAddress > startAddress){
        if (readArea != (startAddress & 0xFFFFF000)) {
            readArea = startAddress & 0xFFFFF000;
            
            outsize = 0;
            result = vm_read_overwrite(target_task, readArea, 4096, (vm_address_t)buffer, &outsize);
            
            if(!outsize){
                printf("stardAddress : %x\n",startAddress);
                fprintf(stderr,"vm_read_overwrite failed: %u\n",startAddress & 0xFFFFF000);
            }
        }
        
        if (result == KERN_SUCCESS) {
            for (int i=0; i<1024; i++) {
                memInfoStruct.address = startAddress;
                memInfoStruct.value = *(int*)((int)buffer + ((startAddress - (startAddress & 0xFFFFF000)) & 0xFFFFFFFc));
                memDataList.push_back(memInfoStruct);
                startAddress += 4;
            }
        }
        startAddress += 4;
    }
    printf("list size : %ld\n",memDataList.size());
}

void readMemory(long number){
    if (attach()) {
        void  *buffer = malloc(4096);
        for(int i = 0;i < regionList.size();i++){
            regionStruct = regionList.at(i);
            vm_address_t startAddress = regionStruct.startAddr;
            vm_address_t endAddress = regionStruct.endAddr;
            getValueArea(startAddress,endAddress,buffer,number);
        }
        free(buffer);
        
        if(task_resume(target_task)){
            printf("Cannot resume task!\n");
        }
    }else{
        printf("attach failed");
    }
}

void reReadMemory(long number){
    if (attach()) {
        vm_address_t startAddress = 0, endAddress = 0;
        
        void  *buffer = malloc(4096);
        
        for(int i = 0;i < findDataList.size();i++){
            findInfoStruct = findDataList.at(i);
            vm_address_t cmp = findInfoStruct.address;
            if((startAddress >= cmp) || (cmp >= endAddress)){
                startAddress   = findInfoStruct.address;
                endAddress     = findInfoStruct.address + MEMREADSIZE;
                getValueArea(startAddress,endAddress,buffer,number);
            }
        }
        free(buffer);
        
        if(task_resume(target_task)){
            printf("Cannot resume task!\n");
        }
    }else{
        printf("attach failed");
    }
}

void getValueAddress(vm_address_t address){
    kern_return_t result;
    void *buffer;
    buffer = malloc(8);
    vm_size_t outsize;
    
    if (attach()) {
        result = vm_read_overwrite(target_task, address, 8, (vm_address_t)buffer, &outsize);
        
        if(!outsize){
            printf("stardAddress : %x\n",address);
            fprintf(stderr,"vm_read_overwrite failed: %u\n",address & 0xFFFFFFFc);
        }
        
        if (result == KERN_SUCCESS) {
            printf("%d\n",*(int*)buffer);
        }
        
        if(task_resume(target_task)){
            printf("Cannot resume task!\n");
        }
    }else{
        printf("attach failed");
    }
    free(buffer);
}