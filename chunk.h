//
//  jana_chunk.h
//  Interpreter
//
//  Created by Akha on 02.07.2024.
//

#ifndef jana_chunk_h
#define jana_chunk_h

#include "common.h"
#include "value.h" // i only remember that i prefired i am so good.

typedef enum {
    OP_RETURN,
    OP_CONSTANT,
    OP_ADD,
    OP_SUBSTRACT,
    OP_MULTIPLY,
    OP_DIV,
} OpCode;

// i wrote a lot of explanation on this and then i lost it all, that's so fcking bad.

typedef struct {
    int count;
    int capacity;
    uint8_t* code;
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);
void freeChunk(Chunk* chunk);
int addConstant(Chunk* chunk, Value value);

#endif /* chunk_h */
