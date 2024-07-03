#include <assert.h>
#include <math.h>
#include "line.h"
#include "log.h"

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static RasterizedLines RasterizeLine(Shape* obj)
{
    // log_info_no_args();
    Line* t = (Line*)obj;
    int X0 = t->p1.x;
    int Y0 = t->p1.y;
    int X1 = t->p2.x;
    int Y1 = t->p2.y;
    // Make sure X0 <= X1
    if (X0 > X1) {
        swap(&X0, &X1);
        swap(&Y0, &Y1);
    }
    int dx = X1 - X0;
    int dy = Y1 - Y0;
    int dy_abs = abs(dy);
    log_debug("dx: %d, dy: %d", dx, dy);

    Scanline* lines = calloc(dy_abs + 1, sizeof(Scanline));
    for (int i = 0; i <= dy_abs; i++) {
        lines[i].x1 = -1;
    }

    // ! Special case for vertical lines and horizontal lines
    if (dx == 0) {
        for (int j = 0; j <= dy; j++) {
            lines[j].y = Y0 + j;
            lines[j].x1 = X0;
            lines[j].x2 = X0;
        }
        RasterizedLines result = { lines, dy_abs + 1 };
        return result;
    }
    if (dy == 0) {
        lines[0].y = Y0;
        lines[0].x1 = X0;
        lines[0].x2 = X1;
        RasterizedLines result = { lines, 1 };
        return result;
    }
    if (dx == dy_abs) {
        for (int i = 0; i <= dx; i++) {
            int j = dy > 0 ? i : -i;
            lines[i].y = Y0 + j;
            lines[i].x1 = X0 + i;
            lines[i].x2 = X0 + i;
        }
        RasterizedLines result = { lines, dy_abs + 1 };
        return result;
    }
    // Digital Differential Analyzer (DDA)
    // int steps = dx > dy_abs ? dx : dy_abs;
    // double slope = dy / (double)dx; // slope can be < 0

    // double x0 = X0 + 0.5;
    // double y0 = Y0 + 0.5;
    // double x1 = X1 + 0.5;
    // double delta_x = dx / (double)steps;
    // double x = x0;
    // double y = y0;
    // while (x <= x1) {
    //     double _i = x - x0;
    //     double _j = dy > 0 ? y - y0 : y0 - y;
    //     int i = round(_i);
    //     int j = round(_j);
    //     if (lines[j].x1 == -1) { // the first point in the line
    //         lines[j].y = dy > 0 ? j + y0 : y0 - j;
    //         lines[j].x1 = i + x0;
    //     }
    //     lines[j].x2 = i + x0;
    //     x += delta_x;
    //     y = y0 + slope * (x - x0); // TODO: add slope*step each time is ok
    // }
    // Bresenham's line algorithm
    int D = 2 * dy - dx;
    int y = Y0;
    for (int x = X0; x <= X1; x++) {
        int j = dy > 0 ? y - Y0 : Y0 - y;
        if (lines[j].x1 == -1) { // the first point in the line
            lines[j].y = dy > 0 ? y : Y0 - j;
            lines[j].x1 = x;
        }
        lines[j].x2 = x;
        if (D > 0) {
            y = y + 1;
            D = D - 2 * dx;
        }
        D = D + 2 * dy;
    }
    RasterizedLines result = { lines, dy_abs + 1 };
    return result;
}

static IShape methods = {
    .Rasterize = RasterizeLine,
    .Destroy = NULL
};

Line* NewLine(int x1, int y1, int x2, int y2)
{
    Line* c = malloc(sizeof(Line));
    assert(!(x1 == x2 && y1 == y2));
    c->methods = &methods;
    c->p1.x = x1;
    c->p1.y = y1;
    c->p2.x = x2;
    c->p2.y = y2;
    return c;
}