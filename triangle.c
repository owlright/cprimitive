#include "stdio.h"
#include "triangle.h"
#include "log.h"
static RasterizedLines RasterizeTrangle(void* obj)
{
    log_info_no_args();
    Triangle* t = (Triangle*)obj;
    Scanline** lines = calloc(3, sizeof(Scanline*));
    for (int i = 0; i < 3; i++) {
        lines[i] = calloc(3, sizeof(Scanline));
    }
    RasterizedLines result = { lines, 3, 3 };
    return result;
}

// ! 2. 将Triangele的方法实现绑定到IShape上
// ! 这里没有实现IShape的Destroy方法，可能会很危险
static IShape triangle_methods = {
    .Rasterize = RasterizeTrangle,
    .Destroy = NULL
};

// ! 3. 实现Triangle的构造函数
Triangle* newTriangle()
{
    Triangle* c = malloc(sizeof(Triangle));
    c->methods = &triangle_methods;
    return c;
}