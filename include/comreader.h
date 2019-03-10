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
    uint32_t speed;
    pthread_t readThread;
    HANDLE hPort;
    portion data;
    mutex dataMtx;
    
    bool open(string & error);
    void close();
    bool send(const char* pdata, uint32_t size);
    bool tune(string & error);
public:
    bool opened;
    
    COMReader(string & port, uint32_t speed, string & error);
    virtual ~COMReader();
    
    static void getList(vector<string>& list);
    bool read();
    uint32_t getChunks(list<PChunk> & chunks, bool & bordersChanged);
};

typedef COMReader* PCOMReader;


#endif /* COMREADER_H */

