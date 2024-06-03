#include <stdint.h>
#include <stdlib.h>
#include "shape.h"
#include "triangle.h"

int main()
{
    Triangle* t = NewTriangle();
    RasterizedLines lines = Rasterize(t);
    DestroyRasterizedLines(&lines);
    free(t);
    return 0;
}