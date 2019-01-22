#ifndef CHUNK_H
#define CHUNK_H

#include <inttypes.h>
#include <memory>

using namespace std;

class Chunk {
public:
    int16_t phono;
    uint16_t spiro;
    uint16_t ecg;

    Chunk(uint64_t data);
    virtual ~Chunk();
};

typedef unique_ptr<Chunk> PChunk;

#endif /* CHUNK_H */

