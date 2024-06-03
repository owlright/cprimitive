#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "shape.h"
#include "line.h"

int main()
{
    // Line* t = NewLine(1, 1, 11, 5);
    // Line* t = NewLine(11, 5, 1, 1);
        Line* t = NewLine(11, 1, 1, 5);
    // Line* t = NewLine(1, 1, 1, 5);
    RasterizedLines lines = Rasterize((Shape*)t);
    for (int i = 0; i < lines.h; i++) {
        printf("y: %d, x1: %d, x2: %d\n", lines.lines[i].y, lines.lines[i].x1, lines.lines[i].x2);
    }
    DestroyRasterizedLines(&lines);
    free(t);
    return 0;
}