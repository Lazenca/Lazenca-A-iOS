#ifdef __LP64__
#include <vector>
#import "Util.h"
#import "process.h"

void getValueArea(vm_address_t startAddress,vm_address_t endAddress, void* buffer,long number,bool check){
    
    kern_return_t result;
    
    long readArea = 0;
    vm_size_t outsize;
    
    while(endAddress > startAddress){
        if(check){
            if (readArea != (startAddress & 0xFFFFFFFFFFFFF000)) {
                readArea = startAddress & 0xFFFFFFFFFFFFF000;
                
                outsize = 0;
                result = vm_read_overwrite(target_task, readArea, 4096, (vm_address_t)buffer, &outsize);
                
                if(!outsize){
                    printf("stardAddress 64 : %lx, %lx\n",startAddress,endAddress);
                    fprintf(stderr,"vm_read_overwrite failed: %lu\n",startAddress & 0xFFFFFFFFFFFFF000);
                }
            }
            
            if (result == KERN_SUCCESS) {
                for (int i=0; i<512; i++) {
                    memInfoStruct.address = startAddress;
                    memInfoStruct.value = *(long*)((char*)buffer + ((startAddress - (startAddress & 0xFFFFFFFFFFFFF000)) & 0xFFFFFFFFFFFFFFF8));
                    memDataList.push_back(memInfoStruct);
                    startAddress += 8;
                }
            }else{
                startAddress += 8;
            }
        }else{
            if (readArea != startAddress) {
                readArea = startAddress;
                
                outsize = 0;
                result = vm_read_overwrite(target_task, readArea, 4096, (vm_address_t)buffer, &outsize);
                
                if(!outsize){
                    printf("stardAddress 64 : %lx, %lx\n",startAddress,endAddress);
                    fprintf(stderr,"vm_read_overwrite failed: %lu\n",startAddress);
                }
            }
            
            if (result == KERN_SUCCESS) {
                for (int i=0; i<512; i++) {
                    memInfoStruct.address = startAddress;
                    memInfoStruct.value = *(long*)((char*)buffer + (startAddress - readArea));
                    memDataList.push_back(memInfoStruct);
                    startAddress += 8;
                }
            }else{
                startAddress += 8;
            }
        }
        
    }
}

void readMemory(long number){
    if (attach()) {
        void  *buffer = malloc(4096);
        
        for(int i = 0;i < regionList.size();i++){
            regionStruct = regionList.at(i);
            
            vm_address_t startAddress = regionStruct.startAddr;
            vm_address_t endAddress = regionStruct.endAddr;
            getValueArea(startAddress,endAddress,buffer,number,1);
            
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
                endAddress     = startAddress + 4096;
                getValueArea(startAddress,endAddress,buffer,number,0);
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
            printf("stardAddress 64 : %lx\n",address);
            fprintf(stderr,"vm_read_overwrite failed: %lu\n",address & 0xFFFFFFFFFFFFFFF8);
            
        }
        
        if (result == KERN_SUCCESS) {
            printf("stardAddress 64 : %lx\n",address);
            printf("Address : %lx, int32 Value: %ld\n",address,*(long*)buffer & 0x00000000FFFFFFFF);
            printf("Address : %lx, int32 Value: %ld\n",address + 4,*(long*)buffer >> 32);
        }
        
        if(task_resume(target_task)){
            printf("Cannot resume task!\n");
        }
    }else{
        printf("attach failed");
    }
    free(buffer);
}
#else
#endif