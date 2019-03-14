#include "filewriter.h"


extern "C" void *writeThreadProc(void *arg) {
    PFileWriter pWriter = (PFileWriter)arg;
    
    pWriter->started = true;
    while(pWriter->started) {
        pWriter->write();
        Sleep(50);
    }
    return NULL;
}





FileWriter::FileWriter(string & error) : out() {
    //Create reading thread
    if (pthread_create(&writeThread, NULL, writeThreadProc, this)) {
        error = "Error create writing thread";
        return;
    }
    
    out.exceptions(ios::failbit | ios::badbit);
    if (!open(error)) close();
}




FileWriter::~FileWriter() {
    close();
}



void FileWriter::write() {
    dataMtx.lock();
    auto it = data.begin();
    while(it != data.end()) {
        uint16_t spiro = it->spiro;
        int16_t photo = it->photo;
        uint16_t ecg = it->ecg;
        out << to_string(ecg) << ";";
        out << to_string(spiro) << ";";
        out << to_string(photo) << ";";
        out << endl;
        data.pop_front();
        it = data.begin();
    }
    dataMtx.unlock();
}




bool FileWriter::open(string & error) {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
    string fileName = "data\\" + oss.str() + ".csv";
    try {
        CreateDirectory("data", NULL);
        out.open(fileName);
    } catch (const exception& ex) {
        string code(ex.what());
        error = "Error open CSV file: " + code + "; file -> " + fileName;
        return false;
    }
    return true;
}



void FileWriter::close() {
    started = false;
    pthread_join(writeThread, NULL);
}