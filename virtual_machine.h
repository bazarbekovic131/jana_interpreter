//
//  virtual_machine.h
//  Interpreter
//
//  Created by Akha on 02.07.2024.
//

#ifndef virtual_machine_h
#define virtual_machine_h

#include "chunk.h"

#define STACK_MAX 256 // not doing this dynamical will lead to stack overflow.

typedef struct {
    Chunk* chunk;
    uint8_t* ip; // byte pointer - instruction pointer | alternative is PC - program counter. that's more understandable.
    Value stack[STACK_MAX];
    Value* stackTop; // first in last out is the stack. top points to where the next value needs to be inserted.
} VirtualMachine;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult; // the interpreter will use this to know how to set the exit code of the process.

void initVM();
void freeVM();

InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();

#endif /* virtual_machine_h */
