#include "chunk.h"

Chunk::Chunk(uint64_t data) {
    uint64_t pcur = (uint64_t)&data;
    pcur++;
    pcur++;
    phono = *((int16_t*) pcur);
    
    pcur++;
    pcur++;
    spiro = *((uint16_t*) pcur);
    
    pcur++;
    pcur++;
    ecg = *((uint16_t*) pcur);
}

Chunk::~Chunk() {
}

