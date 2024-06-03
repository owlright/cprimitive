#ifndef raster_h
#define raster_h

#include <stdint.h>
typedef struct {
    int x, y;
} Point;
typedef struct {
    int y, x1, x2;
    uint32_t alpha;
} Scanline;

typedef struct {
    Scanline** lines;
    int h;
} RasterizedLines;

void DestroyRasterizedLines(RasterizedLines* obj);

#endif


