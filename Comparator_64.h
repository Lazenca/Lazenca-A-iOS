#ifdef __LP64__
#import "Util.h"
void NumberComparator(long value) {
    if (findDataList.size()) {
        for (int i = 0,temp = 0; i < findDataList.size(); i++) {
            findInfoStruct = findDataList.at(i);
            memInfoStruct = memDataList.at(temp);

            for (; memInfoStruct.address <= findInfoStruct.address; temp++) {
                if (memInfoStruct.address == findInfoStruct.address) {
                    if (value == (memInfoStruct.value & 0x00000000FFFFFFFF)) {
                        tempInfoStruct.address = memInfoStruct.address;
                        tempInfoStruct.value = (memInfoStruct.value & 0x00000000FFFFFFFF);
                        tempDataList.push_back(tempInfoStruct);
                        
                        if (i < (findDataList.size()-1)) {
                            i++;
                            findInfoStruct = findDataList.at(i);
                            if (memInfoStruct.address > findInfoStruct.address) {
                                --i;
                                findInfoStruct = findDataList.at(i);
                            }
                        }
                    }
                }
                
                if (memInfoStruct.address + 4 == findInfoStruct.address) {
                    if (value == (memInfoStruct.value >> 32)) {
                        tempInfoStruct.address = memInfoStruct.address+4;
                        tempInfoStruct.value = (memInfoStruct.value >> 32);
                        tempDataList.push_back(tempInfoStruct);
                    }
                }
                
                memInfoStruct = memDataList.at(temp);
            }
            temp++;
        }
    } else {
        for (int i = 0; i < memDataList.size(); i++) {
            memInfoStruct = memDataList.at(i);

            if (value == (memInfoStruct.value & 0x00000000FFFFFFFF)) {
                tempInfoStruct.address = memInfoStruct.address;
                tempInfoStruct.value = (memInfoStruct.value & 0x00000000FFFFFFFF);
                tempDataList.push_back(tempInfoStruct);
            }
            if (value == (memInfoStruct.value >> 32)) {
                tempInfoStruct.address = (memInfoStruct.address + 4);
                tempInfoStruct.value = (memInfoStruct.value >> 32);
                tempDataList.push_back(tempInfoStruct);
            }
        }
    }
    
    findDataList.clear();
    findDataList = tempDataList;
    tempDataList.clear();
    memDataList.clear();
}
#else
#endif