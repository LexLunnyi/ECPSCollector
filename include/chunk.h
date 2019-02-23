#ifndef CHUNK_H
#define CHUNK_H

#include <inttypes.h>
#include <memory>

using namespace std;

class Chunk {
public:
    static int16_t maxPhoto;
    static int16_t minPhoto;
    static uint16_t maxSpiro;
    static uint16_t minSpiro;
    static uint16_t maxECG;
    static uint16_t minECG;
    static bool initValue;
    
    int16_t photo;
    uint16_t spiro;
    uint16_t ecg;

    Chunk(uint64_t data);
    virtual ~Chunk();
    
    static void setSpiroBorders(uint16_t min, uint16_t max) {
        minSpiro = min;
        maxSpiro = max;
    }
    
    static void setPhotoBorders(int16_t min, int16_t max) {
        minPhoto = min;
        maxPhoto = max;
    }
    
    static void setECGBorders(uint16_t min, uint16_t max) {
        minECG = min;
        maxECG = max;
    }
};

typedef unique_ptr<Chunk> PChunk;

#endif /* CHUNK_H */

