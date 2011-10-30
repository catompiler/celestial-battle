#include "tgaimage.h"
#include <fstream>
#include <stddef.h>
#include <iostream>
#include <string.h>
#include <GL/glext.h>

int loadTGAImage(const char* fileName, Image* img)
{
    #pragma pack(push,1)
    struct TGAHeader{
        unsigned char idLength;
        char colorMap;
        char dataType;
        char colorMapInfo[5];
        unsigned short x_origin;
        unsigned short y_origin;
        unsigned short width;
        unsigned short height;
        unsigned char bpp;
        char description;
    };
    #pragma pack(pop)

    const int not_packed = 2;
    const int packed = 10;
/**/
    std::ifstream file(fileName, std::ios::in | std::ios::binary);

    if(!file){
        //std::cout << "File not opened: " << fileName << std::endl;
        return 0;
    }

    TGAHeader tga;

    file.read(reinterpret_cast<char*>(&tga), sizeof(tga));

    if(tga.dataType != packed && tga.dataType != not_packed) return 0;

    int bytepp = tga.bpp == 32 ? 4 : 3;
    size_t data_size = tga.width * tga.height * bytepp;

    char* data = new char[data_size];

    file.seekg(tga.idLength, std::ios_base::cur);

    if(tga.dataType == not_packed){
        file.read(data, data_size);
        size_t npixels = tga.width * tga.height;
        char pixel;
        size_t data_pos = 0;
        //swap r and g
        for(size_t i = 0; i < npixels; i++){
            pixel = data[data_pos];
            data[data_pos] = data[data_pos + 2];
            data[data_pos + 2] = pixel;
            data_pos += bytepp;
        }
    }else{
        size_t npixels = tga.width * tga.height;
        size_t data_pos = 0;
        unsigned char count;
        bool compressed;
        char pixel;
        //size_t i;
        for(size_t i = 0; i < npixels; i++){
            file.read(reinterpret_cast<char*>(&count), sizeof(count));
            compressed = count & 128;
            count &= 127;
            count ++;
            if(!compressed){
                for(size_t j = 0; j < count; j++){
                    file.read(&data[data_pos],bytepp);
                    pixel = data[data_pos];
                    data[data_pos] = data[data_pos + 2];
                    data[data_pos + 2] = pixel;
                    data_pos += bytepp;
                }
            }else{
                file.read(&data[data_pos],bytepp);

                pixel = data[data_pos];
                data[data_pos] = data[data_pos + 2];
                data[data_pos + 2] = pixel;

                data_pos += bytepp;
                size_t nbytes = bytepp * (count - 1);
                //memmove копирует по несколько+ байта
                //memmove(&data[data_pos], &data[data_pos - bytepp], nbytes);
                asm("repnz movsb"::"c"(nbytes),"S"(&data[data_pos - bytepp]),"D"(&data[data_pos]));
                data_pos += nbytes;
            }
            i += count - 1;
        }
    }

    //std::cout << "descr & 0x20: " << static_cast<int>(tga.description & 0x20) << std::endl;
    //if image start at up
    if((tga.description & 0x20) == 0){
        char* data_flipped = new char[data_size];
        int line_size = tga.width * bytepp;
        for(int line = 0; line < data_size; line += line_size){
            memcpy(&data_flipped[line], &data[data_size - line_size - line], line_size);
        }
        delete[] data;
        data = data_flipped;
    }

    img->width = tga.width;
    img->height = tga.height;
    img->bpp = tga.bpp;
    img->pixels = data;

    file.close();

    return 1;
}

GLuint loadTextureTGA(const char* fileName)
{
    Image img;

    if(!loadTGAImage(fileName, &img)){
        return 0;
    }

    GLint internal_format = img.bpp == 32 ? GL_RGBA8 : GL_RGB8;
    GLenum format = img.bpp == 32 ? GL_RGBA : GL_RGB;

    GLuint _res_tex;
    glGenTextures(1, &_res_tex);
    glBindTexture(GL_TEXTURE_2D, _res_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
    glTexImage2D(GL_TEXTURE_2D, 0,internal_format,img.width,img.height,0,
                                  format,GL_UNSIGNED_BYTE,img.pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

    delete[] img.pixels;

    return _res_tex;/**/
}


