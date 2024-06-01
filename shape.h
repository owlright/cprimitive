#ifndef shape_h
#define shape_h

#include "rasterizer.h"
// 前向声明 IShape
typedef struct IShape IShape;
typedef struct Shape Shape;

// ! 接口只包含函数
struct IShape {
    RasterizedLines (*Rasterize)(IShape* this);
    void (*Destroy)(IShape* this);
};

// ! 多态函数
RasterizedLines Rasterize(IShape* this);
void Destroy(IShape* this);

// ! 基类
struct Shape {
    IShape* methods;
};
#endif