#include <stdlib.h>
#include "rasterizer.h"

void DestroyRasterizedLines(RasterizedLines* lines)
{
    free(lines->lines);
}