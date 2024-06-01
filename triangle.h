#ifndef triangle_h
#define triangle_h
#include <stdlib.h>
#include "shape.h"

typedef struct {
    IShape* methods;
    int X1, Y1;
    int X2, Y2;
    int X3, Y3;
} Triangle;

Triangle* newTriangle();

#endif

