#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <fileapi.h>
#include <pthread.h>
#include <synchapi.h>
#include <list>
#include <mutex>
#include <iomanip>
#include <ctime>

#include "chunk.h"
#include "functions.h"

using namespace std;

class FileWriter {
private:
    ofstream out;
    pthread_t writeThread;
    list<Chunk> data;
    mutex dataMtx;
public:
    FileWriter(string & error);
    virtual ~FileWriter();
    bool started;
    
    bool open(string & error);
    void close();
    void write();
    void lock() {dataMtx.lock();}
    void unlock() {dataMtx.unlock();}
    void push(Chunk & elem) {data.emplace_back(elem.ecg, elem.spiro, elem.photo);}
};

typedef FileWriter* PFileWriter;

#endif /* FILEWRITER_H */

