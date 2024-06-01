#include <stdlib.h>
#include "rasterizer.h"

void DestroyRasterizedLines(void* obj)
{
    // TODO free lines
    RasterizedLines* _lines = (RasterizedLines*)obj;
    for (int i = 0; i < _lines->h; i++) {
        // for (int j = 0; j < _lines->w; j++) {
            free(_lines->lines[i]);
        // }
    }
}