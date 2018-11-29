#ifndef COMREADER_H
#define COMREADER_H


#include "functions.h"

#include <string>
#include <vector>
#include <windows.h>

using namespace std;

class COMReader {
private:
public:
    COMReader() {}
    virtual ~COMReader() {}
    
    void getList(vector<string>& list);
};



#endif /* COMREADER_H */

