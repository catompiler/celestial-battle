#include "tgareader.h"
#include "tga/tga.h"
#include "tga/texture.h"


ENGINE_NAMESPACE_BEGIN


TgaReader::TgaReader()
    :Reader<GL::Texture2D>()
{
}

TgaReader::~TgaReader()
{
}
    
GL::Texture2D* TgaReader::read(const std::string& filename_) const
{
    return tga::texture(filename_);
}


ENGINE_NAMESPACE_END

