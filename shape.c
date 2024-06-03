#include <assert.h>
#include <stddef.h> // Include the header file that declares 'NULL'
#include "shape.h"
#define REGISTER_FUNCTION(ReturnType, FunName, ...)                  \
    ReturnType FunName(Shape* this, ##__VA_ARGS__)                   \
    {                                                                \
        assert(this != NULL);                                        \
        assert(this->methods->FunName != NULL);                      \
        return this->methods->FunName(this, ##__VA_ARGS__); \
    }

REGISTER_FUNCTION(RasterizedLines, Rasterize);
// RasterizedLines Rasterize(Shape* this)
// {
//     assert(this!=NULL);
//     assert(this->methods->Rasterize != NULL);
//     return this->methods->Rasterize(this);
// }
REGISTER_FUNCTION(void, Destroy);
// void Destroy(Shape* this)
// {
//     assert(this!=NULL);
//     assert(this->methods->Destroy != NULL);
//     this->methods->Destroy(this);
// }