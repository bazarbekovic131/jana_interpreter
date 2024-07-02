//
//  memory.h
//  Interpreter
//
//  Created by Akha on 02.07.2024.
//

#ifndef memory_h
#define memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), \
        sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

void* reallocate(void* pointer, size_t oldSize, size_t newSize);

/*
 * oldSize             | newSize                             | Operation
 * ------------------  | ----------------------------------  | -----------------------------------
 * 0                   | Non‑zero                            | Allocate new block.
 * Non‑zero            | 0                                   | Free the chunk allocation allocation.
 * Non‑zero            | Smaller                             | Shrink existing allocated chunk.
 * Non‑zero            | Larger                              | Grow existing allocated chunk.
 */

#endif /* memory_h */
