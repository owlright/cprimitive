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

// ! 以下实现将grid的左上角坐标视作grid自身坐标
// plow line slope between -1 and 1
static void RasterizeLineLow(int x0, int y0, int x1, int y1, Scanline* lines)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    int D = 2 * dy - dx;
    int y = y0;
    int line_number = 0;
    for (int x = x0; x <= x1; x++) {
        line_number = abs(y - y0);
        if (lines[line_number].x1 == -1) { // the first point in the line
            lines[line_number].x1 = x;
            lines[line_number].y = y;
        }
        lines[line_number].x2 = x; // update x2 anyway
        if (D > 0) {
            y = y + yi;
            D = D + 2 * dy - 2 * dx;
        } else {
            D = D + 2 * dy;
        }
    }
}

// high line slope greater than 1 or less than -1
static void RasterizeLineHigh(int x0, int y0, int x1, int y1, Scanline* lines)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int D = 2 * dx - dy;
    int x = x0;
    int line_number = 0;
    for (int y = y0; y <= y1; y++) {
        line_number = y - y0 > 0 ? y - y0 : y0 - y; // maybe abs() is ok
        if (lines[line_number].x1 == -1) { // the first point in the line
            lines[line_number].x1 = x;
            lines[line_number].y = y;
        }
        lines[line_number].x2 = x; // update x2 anyway
        if (D > 0) {
            x = x + xi;
            D = D + 2 * dx - 2 * dy;
        } else {
            D = D + 2 * dx;
        }
    }
}

static RasterizedLines RasterizeLine(Shape* obj)
{
    // log_info_no_args();
    Line* t = (Line*)obj;
    int X0 = t->p1.x;
    int Y0 = t->p1.y;
    int X1 = t->p2.x;
    int Y1 = t->p2.y;

    int dx = X1 - X0;
    int dy = Y1 - Y0;
    log_debug("dx: %d, dy: %d", dx, dy);

    Scanline* lines = calloc(abs(dy) + 1, sizeof(Scanline));
    for (int i = 0; i <= abs(dy); i++) {
        lines[i].x1 = -1;
    }
    RasterizedLines result;
    // ! Special case for vertical lines and horizontal lines
    if (dx == 0) {
        for (int j = 0; j <= dy; j++) {
            lines[j].y = Y0 + j;
            lines[j].x1 = X0;
            lines[j].x2 = X0;
        }
        result.lines = lines;
        result.h = abs(dy) + 1;
        return result;
    }
    if (dy == 0) {
        lines[0].y = Y0;
        lines[0].x1 = X0;
        lines[0].x2 = X1;
        result.lines = lines;
        result.h = 1;
        return result;
    }
    if (dx == abs(dy)) {
        for (int i = 0; i <= dx; i++) {
            int j = dy > 0 ? i : -i;
            lines[i].y = Y0 + j;
            lines[i].x1 = X0 + i;
            lines[i].x2 = X0 + i;
        }
        result.lines = lines;
        result.h = abs(dy) + 1;
        return result;
    }

    // Bresenham's line algorithm
    if (abs(dy) < abs(dx)) { // |slope| < 1
        if (X0 > X1) {
            RasterizeLineLow(X1, Y1, X0, Y0, lines);
        } else {
            RasterizeLineLow(X0, Y0, X1, Y1, lines);
        }
    } else {
        if (Y0 > Y1) {
            RasterizeLineHigh(X1, Y1, X0, Y0, lines);
        } else {
            RasterizeLineHigh(X0, Y0, X1, Y1, lines);
        }
    }
    result.lines = lines;
    result.h = abs(dy) + 1;
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