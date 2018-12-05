#ifndef COMREADER_H
#define COMREADER_H


#include "functions.h"

#include <string>
#include <vector>
#include <windows.h>
//#include <>

using namespace std;

class COMReader {
private:
    string port;
    unsigned int speed;
    pthread_t readThread;
    
    HANDLE hPort;
public:
    bool opened;
    
    COMReader(string & port, unsigned int speed, string & error);
    virtual ~COMReader();
    
    static void getList(vector<string>& list);
    bool open(string & error);
    void close();
    bool read();
    bool send(const char* pdata, unsigned int size);
    bool tune(string & error);
};

typedef COMReader* PCOMReader;


#endif /* COMREADER_H */

