#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int Y, X1, X2;
    uint32_t Alpha;
} Scanline;

typedef struct {
    Scanline** lines;
    int w, h;
} RasterizedLines;

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


// Declare an interface for a shape
typedef struct {
    // Function pointers for the interface functions
    RasterizedLines (*Rasterize)(void*);
    void (*Destroy)(void*);
} IShape;

// Define a struct for a circle
typedef struct {
    int X1, Y1;
    int X2, Y2;
    int X3, Y3;
    IShape* shape;
} ITriangle;

RasterizedLines Rasterize(void* obj)
{
    ITriangle* t = (ITriangle*)obj;
    Scanline** lines = calloc(3, sizeof(Scanline*));
    for (int i = 0; i < 3; i++) {
        lines[i] = calloc(3, sizeof(Scanline));
    }
    RasterizedLines result = { lines, 3, 3 };
    return result;
}

// Create a global instance of the interface struct
IShape Triangle = {
    Rasterize
};

ITriangle* newTriangle()
{
    ITriangle* c = malloc(sizeof(ITriangle));
    c->shape = &Triangle;
    return c;
}

int main()
{
    ITriangle* t = newTriangle();
    RasterizedLines lines = t->shape->Rasterize(t);
    DestroyRasterizedLines(&lines);
    free(t);
    return 0;
}