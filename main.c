//
//  main.c
//  Interpreter
//  http://www.craftinginterpreters.com/chunks-of-bytecode.html
//  Created by Akha on 02.07.2024.
//  Based on the tutorial above

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "chunk.h" // did this on prefire i am so fkicn good in C.
#include "debug.h"
#include "virtual_machine.h"

static void repl(void) {
    char line[1024];

    for (;;) {
        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }

        interpret(line);
    }
}

static char* readFile(const char* path) {
    FILE* file = fopen(path, "rb"); // open the file with FILE* file = fopen("path", "mode")

    if (file == NULL) { // check if error by opening the file on the given path
        fprintf(stderr, "Could not open the file \"%s\"\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(fileSize + 1);
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);

    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file \"%s\"\n", path);
        exit(74);
    }

    buffer[bytesRead] = '\0';

    fclose(file);

    if (buffer == NULL) { // error check: not enough memory
        fprintf(stderr, "Not enough memory to read \"%s\"\n", path);
        exit(74);
    }
    return buffer;
}

static void runFile(const char* path) {
    char* source = readFile(path);
    InterpretResult result = interpret(source);
    free(source);

    if (result == INTERPRET_COMPILE_ERROR) exit(65);
    if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

int main(int argc, const char * argv[]) {
    initVM();
    
    if (argc == 1 ) {
        repl();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage: jana [path]\n");
        exit(64); // why 64
    }

    freeVM();
    
    return 0;
}

void test_0(void) {
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    constant = addConstant(&chunk, 3.4);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);
    writeChunk(&chunk, OP_ADD, 123);
    constant = addConstant(&chunk, 5.6);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_DIV, 123);
    writeChunk(&chunk, OP_NEGATE, 123); // test negation instruction

    writeChunk(&chunk, OP_RETURN, 123);
    disassembleChunk(&chunk, "test chunk");
    interpret_chunk(&chunk); // TODO:
     // ... freeVM(); freeChunk(&chunk);
 }
