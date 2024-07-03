#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "shape.h"
#include "line.h"
#define CASES_NUMBER 4
int main()
{
    int positions[CASES_NUMBER][4] = {
        { 1, 1, 11, 1 },
        { 1, 1, 1, 11 },
        { 1, 1, 5, 5 },
        { 1, 5, 5, 1 },
    };
    for (int i = 0; i < CASES_NUMBER; i++) {
        printf("case %d: (%d, %d) -> (%d, %d)\n", i + 1, positions[i][0], positions[i][1], positions[i][2], positions[i][3]);
        Line* t = NewLine(positions[i][0], positions[i][1], positions[i][2], positions[i][3]);
        RasterizedLines lines = Rasterize((Shape*)t);
        for (int i = 0; i < lines.h; i++) {
            printf("x1: %-4d x2: %-4d y: %-4d\n",  lines.lines[i].x1, lines.lines[i].x2, lines.lines[i].y);
        }
        DestroyRasterizedLines(&lines);
        free(t);
        printf("\n");
    }
    return 0;
}