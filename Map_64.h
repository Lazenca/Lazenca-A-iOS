#ifdef __LP64__
#include <vector>
#import "Util.h"

int findWriteableRegions(){
    vm_size_t size;
    vm_address_t address;
    natural_t nesting_depth;
    mach_msg_type_number_t infoCnt;
    
    regionList.clear();
    

    size = 0LL;
    address = 0LL;
    struct vm_region_submap_info_64 info;
    infoCnt = VM_REGION_SUBMAP_INFO_COUNT_64;
    
    for (; !vm_region_recurse_64(target_task,&address,&size,&nesting_depth,(vm_region_recurse_info_t)&info,&infoCnt);) {
        if (info.is_submap) {
            ++nesting_depth;
        }else{
            if ((info.protection & (VM_PROT_WRITE | VM_PROT_READ)) == 3 && (info.max_protection & (VM_PROT_WRITE | VM_PROT_READ)) == 3 && address < searchRange) {
                regionStruct.startAddr = address;
                regionStruct.endAddr = size + address;
                regionStruct.size = size;
                regionList.push_back(regionStruct);
                printf("region 64: %016lx-%016lx\n",regionStruct.startAddr,regionStruct.endAddr);
            }
            address += size;
        }
    }
    return 1;
}


void setRegion(){
    regionList.clear();
    printf("SetRegion - target_task : %d\n",target_task);

    findWriteableRegions();

    printf("region Count %lu\n",regionList.size());
}
#else
#endif