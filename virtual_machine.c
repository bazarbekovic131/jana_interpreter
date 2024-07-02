//
//  virtual_machine.c
//  Interpreter
//
//  Created by Akha on 02.07.2024.
//

#include "common.h"
#include "virtual_machine.h"

VirtualMachine vm;

void initVM() {
    
}

void freeVM() {
    
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++) // Instruction pointer will always have the address of the next instruction.
    for (;;) {
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_RETURN:
                return INTERPRET_OK;
                
            default:
                return INTERPRET_COMPILE_ERROR;
        }
    }
#undef READ_BYTE
}


InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code; // IP keeps track of where VM is
    return run();
}

