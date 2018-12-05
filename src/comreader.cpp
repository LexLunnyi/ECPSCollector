#include "comreader.h"



extern "C" void *readThreadProc(void *arg) {
    PCOMReader reader = (PCOMReader)arg;
    while(reader->opened) {
        reader->opened = reader->read();
        Sleep(10);
    }
    
    reader->close();

    return NULL;
}



COMReader::COMReader(string & port, unsigned int speed, string & error) {
    this->port = port;
    this->speed = speed;
    error = "";
    opened = false;
    
    //Open port
    if (!open(error)) {
        return;
    }
    
    //Create reading thread
    if (pthread_create(&readThread, NULL, readThreadProc, this)) {
        error = "Error create display thread";
        close();
        return;
    }
    
    //Set COM-port speed
    if (!tune(error)) {
        opened = false;
        pthread_join(readThread, NULL);
        return;
    }
    
    //Send init char
    char init = 0x01;
    if (!send(&init, 1)) {
        error = "Error send init char";
        opened = false;
        pthread_join(readThread, NULL);
    }
}



COMReader::~COMReader() {
    opened = false;
    pthread_join(readThread, NULL);
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
    //hPort = CreateFile(port.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
    hPort = CreateFile("COM4", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
    if (hPort == INVALID_HANDLE_VALUE) {
        DWORD lastError = GetLastError();
        error = "code -> " + to_string(lastError);
        opened = true;
        return false;
    }
    
    return true;
}




void COMReader::close() {
    CloseHandle(hPort);
}



bool COMReader::read() {
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
    //dcbSerialParameters.DCBlength = sizeof(DCB);
    
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
        case 9600: dcbSerialParameters.BaudRate = CBR_110;
            break;
        case 14400: dcbSerialParameters.BaudRate = CBR_300;
            break;
        case 19200: dcbSerialParameters.BaudRate = CBR_600;
            break;
        case 38400: dcbSerialParameters.BaudRate = CBR_1200;
            break;
        case 57600: dcbSerialParameters.BaudRate = CBR_2400;
            break;
        case 115200: dcbSerialParameters.BaudRate = CBR_4800;
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