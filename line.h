#ifndef line_h
#define line_h
#include <stdlib.h>
#include "shape.h"

typedef struct {
    IShape* methods;
    Point p1, p2;
} Line;

Line* NewLine(int x1, int y1, int x2, int y2);

#endif
