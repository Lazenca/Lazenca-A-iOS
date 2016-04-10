#import "Util.h"

void SmallerComparator() {
    if(memDataList.size() == findDataList.size()){
        for (int i = 0; i < findDataList.size(); i++) {
            findInfoStruct = findDataList.at(i);
            memInfoStruct = memDataList.at(i);

            if (memInfoStruct.address == findInfoStruct.address) {
                if (findInfoStruct.value > memInfoStruct.value) {
                    tempDataList.push_back(memInfoStruct);
                }
            }
        }
    } else{
        int temp = 0;
        for(int i = 0; i < findDataList.size();i++){
            findInfoStruct = findDataList.at(i);
            memInfoStruct = memDataList.at(temp);
            
            for(;memInfoStruct.address <= findInfoStruct.address;temp++){
                memInfoStruct = memDataList.at(temp);
                
                if (memInfoStruct.address == findInfoStruct.address) {
                    if (findInfoStruct.value > memInfoStruct.value) {
                        tempDataList.push_back(memInfoStruct);
                    }
                }
            }
        }
    }
    
    findDataList.clear();
    findDataList = tempDataList;
    tempDataList.clear();
    memDataList.clear();
}

void LagerComparator() {
    if(memDataList.size() == findDataList.size()){
        for (int i = 0; i < findDataList.size(); i++) {
            findInfoStruct = findDataList.at(i);
            memInfoStruct = memDataList.at(i);
            
            if (memInfoStruct.address == findInfoStruct.address) {
                if (findInfoStruct.value < memInfoStruct.value) {
                    tempDataList.push_back(memInfoStruct);
                }
            }
        }
    } else{
        int temp = 0;
        for(int i = 0; i < findDataList.size();i++){
            findInfoStruct = findDataList.at(i);
            memInfoStruct = memDataList.at(temp);
            
            for(;memInfoStruct.address <= findInfoStruct.address;temp++){
                memInfoStruct = memDataList.at(temp);
                if (memInfoStruct.address == findInfoStruct.address) {
                    if (findInfoStruct.value < memInfoStruct.value) {
                        tempDataList.push_back(memInfoStruct);
                    }
                }
            }
        }
    }
    
    findDataList.clear();
    findDataList = tempDataList;
    tempDataList.clear();
    memDataList.clear();
}

void EqualComparator() {
    if(memDataList.size() == findDataList.size()){
        for (int i = 0; i < findDataList.size(); i++) {
            findInfoStruct = findDataList.at(i);
            memInfoStruct = memDataList.at(i);

            if (memInfoStruct.address == findInfoStruct.address) {
                if (findInfoStruct.value != memInfoStruct.value) {
                    tempDataList.push_back(memInfoStruct);
                }
            }
        }
    } else{
        int temp = 0;
        for(int i = 0; i < findDataList.size();i++){
            findInfoStruct = findDataList.at(i);
            memInfoStruct = memDataList.at(temp);
            
            for(;memInfoStruct.address <= findInfoStruct.address;temp++){
                memInfoStruct = memDataList.at(temp);
                if (memInfoStruct.address == findInfoStruct.address) {
                    if (findInfoStruct.value == memInfoStruct.value) {
                        tempDataList.push_back(memInfoStruct);
                    }
                }
            }
        }
    }
    
    findDataList.clear();
    findDataList = tempDataList;
    tempDataList.clear();
    memDataList.clear();
}

void NotEqualComparator() {
    if(memDataList.size() == findDataList.size()){
        for (int i = 0; i < findDataList.size(); i++) {
            findInfoStruct = findDataList.at(i);
            memInfoStruct = memDataList.at(i);
            if (memInfoStruct.address == findInfoStruct.address) {
                if (findInfoStruct.value != memInfoStruct.value) {
                    tempDataList.push_back(memInfoStruct);
                }
            }
        }
    } else{
        int temp = 0;
        for(int i = 0; i < findDataList.size();i++){
            findInfoStruct = findDataList.at(i);
            memInfoStruct = memDataList.at(temp);
            
            for(;memInfoStruct.address <= findInfoStruct.address;temp++){
                memInfoStruct = memDataList.at(temp);
                if (memInfoStruct.address == findInfoStruct.address) {
                    if (findInfoStruct.value != memInfoStruct.value) {
                        tempDataList.push_back(memInfoStruct);
                    }
                }
            }
        }
    }
    
    findDataList.clear();
    findDataList = tempDataList;
    tempDataList.clear();
    memDataList.clear();
}

void NumberComparator(long value) {
    if (findDataList.size()) {
        int temp = 0;
        for (int i = 0; i < findDataList.size(); i++) {
            findInfoStruct = findDataList.at(i);
            memInfoStruct = memDataList.at(temp);
            
            for (; memInfoStruct.address <= findInfoStruct.address; temp++) {
                
                if (memInfoStruct.address == findInfoStruct.address) {
                    if (value == memInfoStruct.value) {
                        tempDataList.push_back(memInfoStruct);
                    }
                }
                memInfoStruct = memDataList.at(temp);
            }
            temp++;
            
        }
    } else {
        for (int i = 0; i < memDataList.size(); i++) {
            memInfoStruct = memDataList.at(i);
            if (value == memInfoStruct.value) {
                tempDataList.push_back(memInfoStruct);
            }
        }
    }
    
    findDataList.clear();
    findDataList = tempDataList;
    tempDataList.clear();
    memDataList.clear();
}

