#ifndef _TGA_IMAGE_H_
#define _TGA_IMAGE_H_

#include <GL/gl.h>

struct Image{
    int width;
    int height;
    int bpp;
    char* pixels;
};

int loadTGAImage(const char* fileName, Image* img);
GLuint loadTextureTGA(const char* fileName);

#endif// _TGA_IMAGE_H_
