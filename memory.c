//
//  memory.c
//  Interpreter
//
//  Created by Akha on 02.07.2024.
//

#include <stdlib.h>
#include "memory.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
      if (newSize == 0) {
            free(pointer);
            return NULL;
      }

    void* result = realloc(pointer, newSize);
    if (result == NULL) exit(1);
    return result;
}
