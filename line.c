#include "line.h"
#include "log.h"
static RasterizedLines RasterizeLine(void* obj)
{
    log_info_no_args();
    Line* t = (Line*)obj;
    size_t h = 1;
    if (t->Y1 > t->Y2) {
        h += t->Y1 - t->Y2;
    } else {
        h += t->Y2 - t->Y1;
    }
    Scanline** lines = calloc(h, sizeof(Scanline*));
    // Bresenham's line algorithm

    RasterizedLines result = { lines, h };
    return result;
}

static IShape methods = {
    .Rasterize = RasterizeLine,
    .Destroy = NULL
};

Line* NewLine(size_t x1, size_t y1, size_t x2, size_t y2)
{
    Line* c = malloc(sizeof(Line));
    c->methods = &methods;
    c->X1 = x1;
    c->Y1 = y1;
    c->X2 = x2;
    c->Y2 = y2;
    return c;
}