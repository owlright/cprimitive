#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "shape.h"
#include "line.h"

int main()
{
    {
        // case 1:  (1, 1) -> (11, 5) slope 0.4 < 1
        Line* t = NewLine(1, 1, 11, 5);
        RasterizedLines lines = Rasterize((Shape*)t);
        for (int i = 0; i < lines.h; i++) {
            printf("y: %-4d x1: %-4d x2: %-4d\n", lines.lines[i].y, lines.lines[i].x1, lines.lines[i].x2);
        }
        DestroyRasterizedLines(&lines);
        free(t);
    }
    {
        // case 2:  (1, 1) -> (11, 5) slope 2.5 < 1
        Line* t = NewLine(1, 1, 5, 11);
        RasterizedLines lines = Rasterize((Shape*)t);
        for (int i = 0; i < lines.h; i++) {
            printf("y: %-4d x1: %-4d x2: %-4d\n", lines.lines[i].y, lines.lines[i].x1, lines.lines[i].x2);
        }
        DestroyRasterizedLines(&lines);
        free(t);
    }
    {
        // case 3:  (11, 5) -> (1, 1)
        Line* t = NewLine(11, 5, 1, 1);
        RasterizedLines lines = Rasterize((Shape*)t);
        for (int i = 0; i < lines.h; i++) {
            printf("y: %-4d x1: %-4d x2: %-4d\n", lines.lines[i].y, lines.lines[i].x1, lines.lines[i].x2);
        }
        DestroyRasterizedLines(&lines);
        free(t);
    }
    {
        // case 4:  (1, 1) -> (1, 5) slope infinty
        Line* t = NewLine(1, 1, 1, 5);
        RasterizedLines lines = Rasterize((Shape*)t);
        for (int i = 0; i < lines.h; i++) {
            printf("y: %-4d x1: %-4d x2: %-4d\n", lines.lines[i].y, lines.lines[i].x1, lines.lines[i].x2);
        }
        DestroyRasterizedLines(&lines);
        free(t);
    }

    return 0;
}