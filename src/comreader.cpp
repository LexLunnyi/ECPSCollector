#include "comreader.h"



extern "C" void *readThreadProc(void *arg) {
    PCOMReader reader = (PCOMReader)arg;
    while(reader->opened) {
        //if (!reader->readAsync()) break;
        if (!reader->read()) break;
        Sleep(50);
    }
    //wxMessageBox("Thread stopped", "DEBUG", wxOK | wxICON_INFORMATION);
    return NULL;
}



COMReader::COMReader(string & port, unsigned int speed, string & error) {
    this->port = port;
    this->speed = speed;
    error = "";
    opened = false;
    
    //Open port
    if (!open(error)) return;
    
    //Set COM-port speed
    if (!tune(error)) {
        CloseHandle(hPort);
        return;
    }
    
    //Send init char
    char init = 0x40;
    if (!send(&init, 1)) {
        error = "Error send init char";
        CloseHandle(hPort);
    }
    
    //Create reading thread
    if (pthread_create(&readThread, NULL, readThreadProc, this)) {
        error = "Error create display thread";
        CloseHandle(hPort);
        return;
    }
}



COMReader::~COMReader() {
    close();
}



void COMReader::getList(vector<string>& list) {
    list.clear();

    TCHAR lpTargetPath[5000];
    
    list.clear();
    for (unsigned int i = 0; i < 255; i++) {
        string COMName = "COM" + to_string(i);
        DWORD res = QueryDosDevice(COMName.c_str(), (LPSTR)lpTargetPath, 5000);
        if (res != 0) list.push_back(COMName);
    }
}




bool COMReader::open(string & error) {
    //"\\\\.\\COM4"
    hPort = CreateFile(port.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
    //hPort = CreateFile("COM4", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
    if (hPort == INVALID_HANDLE_VALUE) {
        DWORD lastError = GetLastError();
        error = "code -> " + to_string(lastError);
        return false;
    }
    opened = true;
    
    return true;
}




void COMReader::close() {
    if (opened) {
        opened = false;
        pthread_join(readThread, NULL);
        //Send by char
        char by = 0x40;
        send(&by, 1);
        CloseHandle(hPort);
    }
}



bool COMReader::read() {
    static const unsigned int ECPS_WORD_SIZE = sizeof(uint64_t);
    DWORD bytesRead;
    
    uint64_t buffer = 0;
    if (!ReadFile(hPort, &buffer, ECPS_WORD_SIZE, &bytesRead, 0)) {
        return false;
    }

    dataMtx.lock();
    data.push_back(buffer);
    if (data.size() > MAX_QUEUE_SIZE) data.pop_front();
    dataMtx.unlock();
    
    return true;
}



bool COMReader::send(const char* pdata, unsigned int size) {
    DWORD count;
    if (!WriteFile(hPort, pdata, size, &count, 0)){
        return false;
    }

    return true;
}




bool COMReader::tune(string & error) {
    DCB dcbSerialParameters;
    SecureZeroMemory(&dcbSerialParameters, sizeof(DCB));
    dcbSerialParameters.DCBlength = sizeof(DCB);
    
    if (!GetCommState(hPort, &dcbSerialParameters)) {
        error = "error read serial options -> " + to_string(GetLastError());
        return false;
    }

    dcbSerialParameters.BaudRate = CBR_9600;
    switch (speed) {
        case 110: dcbSerialParameters.BaudRate = CBR_110;
            break;
        case 300: dcbSerialParameters.BaudRate = CBR_300;
            break;
        case 600: dcbSerialParameters.BaudRate = CBR_600;
            break;
        case 1200: dcbSerialParameters.BaudRate = CBR_1200;
            break;
        case 2400: dcbSerialParameters.BaudRate = CBR_2400;
            break;
        case 4800: dcbSerialParameters.BaudRate = CBR_4800;
            break;
        case 9600: dcbSerialParameters.BaudRate = CBR_9600;
            break;
        case 14400: dcbSerialParameters.BaudRate = CBR_14400;
            break;
        case 19200: dcbSerialParameters.BaudRate = CBR_19200;
            break;
        case 38400: dcbSerialParameters.BaudRate = CBR_38400;
            break;
        case 57600: dcbSerialParameters.BaudRate = CBR_57600;
            break;
        case 115200: dcbSerialParameters.BaudRate = CBR_115200;
            break;
    }
    dcbSerialParameters.ByteSize = 8;
    dcbSerialParameters.StopBits = ONESTOPBIT;
    dcbSerialParameters.Parity = NOPARITY;
    dcbSerialParameters.fDtrControl = DTR_CONTROL_DISABLE;
    
    if (!SetCommState(hPort, &dcbSerialParameters)) {
        error = "error set serial options -> " + to_string(GetLastError());
        return false;
    }
    
    PurgeComm(hPort, PURGE_RXCLEAR | PURGE_TXCLEAR);
    return true;
}



unsigned int COMReader::getChunks(list<PChunk> & chunks, bool & bordersChanged) {
    dataMtx.lock();
    unsigned int res = data.size();

    int16_t maxPhoto = Chunk::maxPhoto;
    int16_t minPhoto = Chunk::minPhoto;
    uint16_t maxSpiro = Chunk::maxSpiro;
    uint16_t minSpiro = Chunk::minSpiro;
    uint16_t maxECG = Chunk::maxECG;
    uint16_t minECG = Chunk::minECG;
    
    for(portion::iterator it = data.begin(); it != data.end(); it++) {
        //ecg.push_back(Chunk(*it));
        chunks.push_back(unique_ptr<Chunk>(new Chunk(*it)));
    }
    
    data.clear();
    dataMtx.unlock();
    
    bordersChanged = ((maxPhoto != Chunk::maxPhoto) || (minPhoto != Chunk::minPhoto) || 
        (maxSpiro != Chunk::maxSpiro) || (minSpiro != Chunk::minSpiro) || 
        (maxECG != Chunk::maxECG) || (minECG != Chunk::minECG));
            
    return res;
}




bool COMReader::readAsync() {
    DWORD dwRead;
    DWORD dwRes;
    BOOL fWaitingOnRead = false;
    OVERLAPPED osReader;
    SecureZeroMemory(&osReader, sizeof (OVERLAPPED));
    uint8_t buffer = 0;

    // Create the overlapped event. Must be closed before exiting
    // to avoid a handle leak.
    osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (osReader.hEvent == NULL) return false;
    // Error creating overlapped event; abort.

    if (!fWaitingOnRead) {
        // Issue read operation.
        if (!ReadFile(hPort, &buffer, 1, &dwRead, &osReader)) {
            if (GetLastError() != ERROR_IO_PENDING) {
                // read not delayed?
                // Error in communications; report it.
                return false;
            } else {
                fWaitingOnRead = true;
            }
        } else {
            // read completed immediately
            dataMtx.lock();
            data.push_back(buffer);
            if (data.size() > MAX_QUEUE_SIZE) data.pop_front();
            dataMtx.unlock();
            return true;
        }
    }

    if (fWaitingOnRead) {
        dwRes = WaitForSingleObject(osReader.hEvent, 500);
        switch (dwRes) {
                // Read completed.
            case WAIT_OBJECT_0:
                if (!GetOverlappedResult(hPort, &osReader, &dwRead, FALSE)) {
                    // Error in communications; report it.
                    return false;
                } else {
                    // Read completed successfully.
                    dataMtx.lock();
                    data.push_back(buffer);
                    if (data.size() > MAX_QUEUE_SIZE) data.pop_front();
                    dataMtx.unlock();
                    return true;
                }
                break;

            case WAIT_TIMEOUT:
                // Operation isn't complete yet. fWaitingOnRead flag isn't
                // changed since I'll loop back around, and I don't want
                // to issue another read until the first one finishes.
                //
                // This is a good time to do some background work.
                break;

            default:
                // Error in the WaitForSingleObject; abort.
                // This indicates a problem with the OVERLAPPED structure's
                // event handle.
                return false;
                break;
        }
    }
    return false;
}