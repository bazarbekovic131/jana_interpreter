//
//
//
//
//
//

#ifndef line_h
#define line_h

#include "memory.h"

typedef struct {
    int line;
    int count;
} LineInfo;

void initLine();
void freeLine();
void writeLine();

#endif // line_h