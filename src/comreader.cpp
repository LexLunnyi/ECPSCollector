#include "comreader.h"



void COMReader::getList(vector<string>& list) {
    list.clear();

    TCHAR lpTargetPath[5000]; // buffer to store the path of the COM-ports
    
    list.clear();
    for (unsigned int i = 0; i < 255; i++) {
        string COMName = "COM" + to_string(i);
        DWORD res = QueryDosDevice(COMName.c_str(), (LPSTR)lpTargetPath, 5000);
        if (res != 0) list.push_back(COMName);
    }
}