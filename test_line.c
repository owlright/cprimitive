#include <stdint.h>
#include <stdlib.h>
#include "shape.h"
#include "line.h"

int main()
{
    Line* t = newLine(3, 4, 5, 6);
    RasterizedLines lines = Rasterize(t);
    DestroyRasterizedLines(&lines);
    free(t);
    return 0;
}