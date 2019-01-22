#ifndef COMREADER_H
#define COMREADER_H


#define __STDC_FORMAT_MACROS 1
#include <inttypes.h>

#include <mutex>
#include <string>
#include <vector>
#include <list>
#include <windows.h>
#include <fileapi.h>
//#include <wx/wx.h>

#include "functions.h"
#include "chunk.h"


using namespace std;

typedef list<uint64_t> portion;

class COMReader {
private:
    static const int MAX_QUEUE_SIZE = 10000;
    
    string port;
    unsigned int speed;
    pthread_t readThread;
    HANDLE hPort;
    portion data;
    mutex dataMtx;
    
    bool open(string & error);
    void close();
    bool send(const char* pdata, unsigned int size);
    bool tune(string & error);
public:
    bool opened;
    
    COMReader(string & port, unsigned int speed, string & error);
    virtual ~COMReader();
    
    static void getList(vector<string>& list);
    bool read();
    bool readAsync();
    unsigned int getChunks(list<PChunk> & chunks);
};

typedef COMReader* PCOMReader;


#endif /* COMREADER_H */
