//
//  jana_chunk.c
//  Interpreter
//
//  Created by Akha on 02.07.2024.
//

#include <stdlib.h>
#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

/*

Line Analogs

*/

// void compile(const char* source, Chunk* chunk) {
//     // Tokenize and parse the source code
//     // Convert parsed structures to bytecode
//     // Example for adding a constant:
//     int constant = addConstant(chunk, 1.2);
//     writeChunk(chunk, OP_CONSTANT, line);
//     writeChunk(chunk, constant, line);
// }


// void writeChunk(Chunk* chunk, int bytecode, int lineNumber) {
//     if (chunk->count + 1 > chunk->capacity) {
//         // Code to grow the 'code' array
//     }
//     chunk->code[chunk->count++] = bytecode;

//     // Check if the current line number matches the last line number
//     if (chunk->lineCount > 0 && chunk->lines[chunk->lineCount - 1].lineNumber == lineNumber) {
//         chunk->lines[chunk->lineCount - 1].count++;
//     } else {
//         // Add new line info or grow the 'lines' array
//         if (chunk->lineCount + 1 > chunk->lineCapacity) {
//             // Code to grow the 'lines' array
//         }
//         chunk->lines[chunk->lineCount].lineNumber = lineNumber;
//         chunk->lines[chunk->lineCount].count = 1;
//         chunk->lineCount++;
//     }
// }