#ifndef shape_h
#define shape_h

#include "rasterizer.h"
// 前向声明 IShape
typedef struct IShape IShape;
typedef struct Shape Shape;

// ! 接口只包含函数
struct IShape {
    RasterizedLines (*Rasterize)(Shape* this);
    void (*Destroy)(Shape* this);
};

// ! 基类
struct Shape {
    IShape* methods;
};

// ! 基类方法
RasterizedLines Rasterize(Shape* this);
void Destroy(Shape* this);
#endif