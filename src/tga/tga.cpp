#include "tga.h"
#include <fstream>
#include <string.h>


namespace tga{


bool read(const std::string& fileName_, image_t* img_, direction_t dir_)
{
    std::ifstream file(fileName_, std::ios::in | std::ios::binary);

    if(!file){
        return false;
    }

    header_t tga;

    file.read(reinterpret_cast<char*>(&tga), sizeof(tga));

    if(tga.dataType != packed && tga.dataType != not_packed) return false;
    
    size_t bytepp = tga.bpp >> 3;
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
                //memmove(&data[data_pos], &data[data_pos - bytepp], nbytes);
                asm("repnz movsb"::"c"(nbytes),"S"(&data[data_pos - bytepp]),"D"(&data[data_pos]));
                data_pos += nbytes;
            }
            i += count - 1;
        }
    }
    
    file.close();
    
    img_->width = tga.width;
    img_->height = tga.height;
    img_->bpp = tga.bpp;
    img_->pixels = data;
    
    direction_t img_dir = ((tga.description & 0x20) == 1) ? up_to_down : down_to_up;
    
    if(img_dir != dir_){
        size_t line_size = img_->width * bytepp;
        char* line = new char[line_size];
        
        char* data_front = img_->pixels;
        char* data_end = img_->pixels + data_size - line_size;
        
        size_t data_size2 = line_size * (img_->height >> 1);
        
        for(size_t i = 0; i < data_size2; i += line_size){
            memcpy(line, data_front, line_size);
            memcpy(data_front, data_end, line_size);
            memcpy(data_end, line, line_size);
            data_front += line_size;
            data_end -= line_size;
        }
        delete[] line;
    }
    
    img_->direction = dir_;
    
    return true;
}

bool write(const std::string& fileName_, const image_t* img_)
{
    size_t bpp = img_->bpp;
    
    if(bpp != 24 && bpp != 32) return false;
    
    std::ofstream file(fileName_, std::ios::out | std::ios::binary);

    if(!file){
        return false;
    }

    header_t tga;

    memset(&tga, 0x0, sizeof(header_t));
    
    tga.idLength = 0;
    tga.colorMap = 0;
    tga.dataType = not_packed;
    tga.width = img_->width;
    tga.height = img_->height;
    tga.bpp = bpp;
    if(bpp == 32) tga.description |= 0x8;
    if(img_->direction == up_to_down) tga.description |= 0x20;
    
    file.write(reinterpret_cast<const char*>(&tga), sizeof(header_t));
    //file.write(static_cast<const char*>(img_->pixels), il::size(img_)); // r <-> b :(
    
    size_t bytepp = bpp >> 3;
    size_t data_size = img_->width * img_->height * bytepp;
    
    char pixel[bytepp];
    char p_tmp;
    
    for(size_t i = 0; i < data_size; i += bytepp){
        memcpy(pixel, &static_cast<char*>(img_->pixels)[i], bytepp);
        p_tmp = pixel[0];
        pixel[0] = pixel[2];
        pixel[2] = p_tmp;
        file.write(pixel, bytepp);
    }
    
    file.close();
    
    return true;
}


}

