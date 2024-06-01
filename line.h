#ifndef line_h
#define line_h
#include <stdlib.h>
#include "shape.h"

typedef struct {
    IShape* methods;
    size_t X1, Y1, X2, Y2;
} Line;

Line* newLine(size_t x1, size_t y1, size_t x2, size_t y2);

#endif
