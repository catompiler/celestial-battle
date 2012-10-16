#ifndef _TGA_H_
#define _TGA_H_

#include <stddef.h>
#include <stdint.h>
#include <string>


namespace tga{

#pragma pack(push,1)
typedef struct _header{
    uint8_t idLength;
    int8_t colorMap;
    int8_t dataType;
    int8_t colorMapInfo[5];
    uint16_t x_origin;
    uint16_t y_origin;
    uint16_t width;
    uint16_t height;
    uint8_t bpp;
    int8_t description;
} header_t;
#pragma pack(pop)

enum direction_t{up_to_down = 1, down_to_up = 2};

typedef struct _image{
    size_t width;
    size_t height;
    size_t bpp;
    direction_t direction;
    char* pixels;
} image_t;

enum pack_t{not_packed = 2, packed = 10};

bool read(const std::string& fileName_, image_t* img_, direction_t dir_);
bool write(const std::string& fileName_, const image_t* img_);

}

#endif  //_TGA_H_
