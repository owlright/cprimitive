#include "shape.h"
#include <assert.h>

#define REGISTER_FUNCTION(ReturnType, FunName, Base, ...) \
    ReturnType FunName(Base* this, ##__VA_ARGS__) \
    { \
        assert(this != NULL); \
        assert(this->methods->FunName != NULL); \
        return this->methods->FunName(this, ##__VA_ARGS__); \
    }

REGISTER_FUNCTION(RasterizedLines, Rasterize, Shape);
// RasterizedLines Rasterize(Shape* this)
// {
//     assert(this!=NULL);
//     assert(this->methods->Rasterize != NULL);
//     return this->methods->Rasterize(this);
// }
REGISTER_FUNCTION(void, Destroy, Shape);
// void Destroy(Shape* this)
// {
//     assert(this!=NULL);
//     assert(this->methods->Destroy != NULL);
//     this->methods->Destroy(this);
// }