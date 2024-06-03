#include <stdlib.h>
#include "rasterizer.h"

void DestroyRasterizedLines(RasterizedLines* lines)
{
    for (int i = 0; i < lines->h; i++) {
        free(lines->lines[i]);
    }
}