#include "chunk.h"


int16_t Chunk::maxPhoto = 0;
int16_t Chunk::minPhoto = 0;
uint16_t Chunk::maxSpiro = 0;
uint16_t Chunk::minSpiro = 0;
uint16_t Chunk::maxECG = 0;
uint16_t Chunk::minECG = 0;
bool Chunk::initValue = true;



Chunk::Chunk(uint64_t data) {
    uint64_t pcur = (uint64_t)&data;
    pcur += sizeof(int16_t);
    photo = *((int16_t*) pcur);
    
    pcur += sizeof(uint16_t);
    spiro = *((uint16_t*) pcur);
    
    pcur += sizeof(uint16_t);
    ecg = *((uint16_t*) pcur);
    
    if (initValue) {
        initValue = false;
        maxECG = ecg;
        minECG = ecg;
        maxPhoto = photo;
        minPhoto = photo;
        maxSpiro = spiro;
        minSpiro = spiro;
    } else {
        if (ecg > maxECG) maxECG = ecg;
        if (ecg < minECG) minECG = ecg;
        if (photo > maxPhoto) maxPhoto = photo;
        if (photo > maxPhoto) minPhoto = photo;
        if (spiro > maxSpiro) maxSpiro = spiro;
        if (spiro > maxSpiro) minSpiro = spiro;
    }
}


Chunk::~Chunk() {
}

