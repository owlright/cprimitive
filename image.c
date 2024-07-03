#include "image.h"

void rgb2gray(unsigned char* data, int width, int height)
{
    for (int i = 0; i < width * height; i++)
    {
        unsigned char r = data[i * 3];
        unsigned char g = data[i * 3 + 1];
        unsigned char b = data[i * 3 + 2];
        unsigned char gray = 0.299 * r + 0.587 * g + 0.114 * b;
        data[i * 3] = gray;
        data[i * 3 + 1] = gray;
        data[i * 3 + 2] = gray;
    }
}