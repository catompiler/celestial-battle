#ifndef _TGA_TEXTURE_H_
#define _TGA_TEXTURE_H_

#include <string>
#include "opengl/opengl.h"
#include "gltexture/gltexture.h"


namespace tga{

GL::Texture2D* texture(const std::string& fileName_);

}


#endif  //_TGA_TEXTURE_H_
