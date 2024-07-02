//
//  virtual_machine.h
//  Interpreter
//
//  Created by Akha on 02.07.2024.
//

#ifndef virtual_machine_h
#define virtual_machine_h

#include "chunk.h"

typedef struct {
    Chunk* chunk;
    uint8_t* ip; // byte pointer - instruction pointer | alternative is PC - program counter. that's more understandable.
} VirtualMachine;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult; // the interpreter will use this to know how to set the exit code of the process.

void initVM();
void freeVM();

#endif /* virtual_machine_h */
