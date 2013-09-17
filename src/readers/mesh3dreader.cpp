#include "mesh3dreader.h"
//#include <fstream>
#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <string>
#include <iostream>
#include "resources/resources.h"
#include "opengl/opengl.h"
#include "glbuffer/glbuffer.h"


ENGINE_NAMESPACE_BEGIN


Mesh3dReader::Mesh3dReader()
    :Reader<Mesh>()
{
}

Mesh3dReader::~Mesh3dReader()
{
}

Mesh* Mesh3dReader::read(Resources* resources_, const std::string& filename_) const
{
    std::ifstream file(filename_, std::ios::in | std::ios::binary);
    
    if(!file) return nullptr;
    
    const size_t magic_len = 8;
    const uint8_t magic[magic_len] = {'m','e','s','h','3','d',0,0};
    uint8_t file_magic[magic_len];
    uint32_t version;
    
    
    file.read(reinterpret_cast<char*>(file_magic), magic_len);
    if(file.fail()) return nullptr;
    
    if(!std::equal(magic, magic + magic_len, file_magic)) return nullptr;
    
    _readRawData(file, version);
    if(file.fail()){
        return nullptr;
    }
    
    switch(version){
        case 1:
            return read_version_1(resources_, file);
        default:
            break;
    }
    
    return nullptr;
}

std::string Mesh3dReader::_readStrz(std::ifstream& file) const
{
    std::string res;
    uint8_t c;
    for(;file.good();){
        _readRawData(file, c);
        if(c != 0) res += static_cast<char>(c);
        else break;
    }
    return res;
}

Mesh* Mesh3dReader::read_version_1(Resources* resources_, std::ifstream& file) const
{
    uint32_t attribs_count = 0;
    std::string attrib_name;
    uint32_t count = 0;
    uint32_t comp_count = 0;
    buffer_ptr buffer = nullptr;
    std::vector<char> data;
    size_t size = 0;
    Mesh* mesh = nullptr;
    
    _readRawData(file, count);
    if(file.fail()) return nullptr;
    
    comp_count = 1;
    size = count * comp_count * sizeof(uint32_t);
    
    data.resize(size);
    file.read(data.data(), size);
    if(file.fail()) return nullptr;
    
    buffer = resources_->get<GL::Buffer>();
    if(buffer == nullptr) return nullptr;
    
    buffer->bind(GL_ELEMENT_ARRAY_BUFFER);
    GL::Buffer::setData(GL_ELEMENT_ARRAY_BUFFER, size, data.data(), GL_STATIC_DRAW);
    GL::Buffer::unbind(GL_ELEMENT_ARRAY_BUFFER);
    
    mesh = new Mesh();
    mesh->setIndices(buffer);
    
    _readRawData(file, attribs_count);
    if(file.fail()) {
        delete mesh;
        return nullptr;
    }
    
    for(uint32_t i = 0; i < attribs_count; i ++){
        attrib_name = _readStrz(file);
        if(file.fail()) {
            delete mesh;
            return nullptr;
        }
        _readRawData(file, comp_count);
        if(file.fail()) {
            delete mesh;
            return nullptr;
        }
        _readRawData(file, count);
        if(file.fail()) {
            delete mesh;
            return nullptr;
        }
        size = count * comp_count * sizeof(float);
        data.resize(size);
        file.read(data.data(), size);
        if(file.fail()) {
            delete mesh;
            return nullptr;
        }
        buffer = resources_->get<GL::Buffer>();
        buffer->bind(GL_ARRAY_BUFFER);
        GL::Buffer::setData(GL_ARRAY_BUFFER, size, data.data(), GL_STATIC_DRAW);
        GL::Buffer::unbind(GL_ARRAY_BUFFER);
        //std::cout << "attrib " << attrib_name << " count " << count << std::endl;
        mesh->setAttrib(attrib_name, buffer);
    }
    
    return mesh;
}



ENGINE_NAMESPACE_END


