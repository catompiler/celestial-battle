#ifndef _TGAREADER_H
#define _TGAREADER_H

#include <string>
#include "engine/engine.h"
#include "resources/reader.h"
#include "gltexture/gltexture.h"


ENGINE_NAMESPACE_BEGIN


class TgaReader
    :public Reader<GL::Texture2D>
{
public:
    TgaReader();
    ~TgaReader();
    
    GL::Texture2D* read(Resources* resources_, const std::string& filename_) const;
};


ENGINE_NAMESPACE_END

#endif  //_TGAREADER_H
