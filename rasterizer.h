#ifndef raster_h
#define raster_h

#include <stdint.h>
typedef struct {
    int Y, X1, X2;
    uint32_t Alpha;
} Scanline;

typedef struct {
    Scanline** lines;
    int w, h;
} RasterizedLines;

void DestroyRasterizedLines(void* obj);

#endif


