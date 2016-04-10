#ifdef __LP64__
#include <vector>
#import "Comparator_64.h"
#import "MemRead_64.h"
#import "Map_64.h"
#else
#include <vector>
#import "Comparator.h"
#import "MemRead.h"
#import "Map.h"
#endif

#import "Util.h"
#import "process.h"


//검색 프로세스
void SearchProcess(long number){
    if ((findDataList.size() == 0) && (isCMDRUNNING == 0)) {
        findWriteableRegions();
        readMemory(number);
        isCMDRUNNING++;
    }else{
        reReadMemory(number);
    }
    NumberComparator(number);
    printf("OriginalDatalist Size : %lu\n",findDataList.size());
    printf("Search End\n");
}