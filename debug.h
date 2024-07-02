//
//  debug.h
//  Interpreter
//
//  Created by Akha on 02.07.2024.
//

#ifndef debug_h
#define debug_h

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);

#endif /* debug_h */
