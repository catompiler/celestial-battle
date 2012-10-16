#include "texture.h"
#include "tga/tga.h"


namespace tga{

GL::Texture2D* texture(const std::string& fileName_)
{
    image_t img;
    
    if(!read(fileName_, &img, down_to_up)){
        return NULL;
    }
    
    GLint internal_format = GL_RGB8;
    GLenum format = GL_RGB;
    
    if(img.bpp == 32){
        internal_format = GL_RGBA8;
        format = GL_RGBA;
    }
    
    GL::Texture2D* tex_res = new GL::Texture2D();
    
    tex_res->bind();
    
    tex_res->setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    tex_res->setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //tex_res->setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //tex_res->setParameteri(GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
    tex_res->setImage(0,internal_format,img.width,img.height,
                      format,GL_UNSIGNED_BYTE,img.pixels);
    
    tex_res->unbind();
    
    delete[] img.pixels;
    
    return tex_res;
}

}


