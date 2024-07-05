//
//  virtual_machine.c
//  Interpreter
//
//  Created by Akha on 02.07.2024.
//

#include <stdio.h>
#include "common.h"
#include "virtual_machine.h"
#include "debug.h" // i am good at prefiring these

VirtualMachine vm;

static void resetStack() {
  vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

void freeVM() {
    
}

void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--; // return back to the most recent value
    return *vm.stackTop; // return it's index
}


InterpretResult run() {
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_ADD: {
                double b = pop();
                double a = pop();
                push(a + b);
                break;
            }
            // Handle other opcodes similarly
            case OP_RETURN: {
                return INTERPRET_OK;
            }
        }
    }

    #undef READ_BYTE
    #undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code; // IP keeps track of where VM is
    return run();
}

