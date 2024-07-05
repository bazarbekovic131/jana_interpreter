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
    #define BINARY_OP(op) \
        do { \
            double a = pop(); \
            double b = pop(); \
            push(a op b);  \
        } while (false) \

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("          "); // some text
    
    for (Value* slot; slot<vm.stackTop; slot++) {
        printf("[ ");
        printValue(*slot);
        printf(" ]");
    }
    printf("\n");

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
            case OP_SUBTRACT: {
                double b = pop();
                double a = pop();
                push(a - b);
                break;
            }
            case OP_MULTIPLY: {
                BINARY_OP(*);
                break;
            }
            case OP_DIV: {
                BINARY_OP(/);
                break;
            }
            case OP_NEGATE: {
                push(-pop());
                break;
            }
            // Handle other opcodes similarly
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }

    #undef READ_BYTE
    #undef READ_CONSTANT
    #undef BINARY_OP
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code; // IP keeps track of where VM is
    return run();
}

