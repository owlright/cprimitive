#ifndef line_h
#define line_h
#include <stdlib.h>
#include "shape.h"

typedef struct {
    IShape* methods;
    Point p1, p2;
} Line;

Line* NewLine(size_t x1, size_t y1, size_t x2, size_t y2);

#endif
