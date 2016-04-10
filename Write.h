#import "Util.h"


void MemoryWrite(vm_address_t address,long value){
    vm_size_t outsize;
    vm_address_t startAddress = 0;
    
#ifdef __LP64__
    unsigned int data;
    vm_read_overwrite(target_task, startAddress & 0xFFFFFFFFFFFFFFF8, 8, (vm_address_t)&data, &outsize);
    
    if (outsize) {
        
    }else{
        printf("vm_read_overwrite(%11lx) failed 1.",startAddress & 0xFFFFFFFFFFFFFFF8);
    }
#else
    int data;
    vm_read_overwrite(target_task, startAddress & 0xFFFFFFFC, 8, (vm_address_t)&data, &outsize);
    
    if (outsize) {
        
    }else{
        printf("vm_read_overwrite(%11x) failed 1.",startAddress & 0xFFFFFFFC);
    }
#endif
    
    
#ifdef __LP64__
    unsigned int write_data;
    write_data = value;
#else
    int write_data;
    write_data = value;
#endif
    
    kern_return_t kr;
    kr = vm_write(target_task, address, (vm_address_t)&write_data, 4);
    if(kr){
        printf("Fail %x\n", kr);
    }else{
        printf("Sucess!\n");
    }
}