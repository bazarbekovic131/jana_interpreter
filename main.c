//
//  main.c
//  Interpreter
//  http://www.craftinginterpreters.com/chunks-of-bytecode.html
//  Created by Akha on 02.07.2024.
//  Based on the tutorial above

#include "common.h"
#include "chunk.h" // did this on prefire i am so fkicn good in C.
#include "debug.h"

int main(int argc, const char * argv[]) {
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_RETURN, 123);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);
    return 0;
}
