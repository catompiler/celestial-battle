#ifndef MESH3DREADER_H
#define	MESH3DREADER_H

#include "engine/engine.h"
#include "resources/reader.h"
#include "mesh/mesh.h"
#include <fstream>


ENGINE_NAMESPACE_BEGIN

class Resources;

class Mesh3dReader
    :public Reader<Mesh>
{
public:
    Mesh3dReader();
    ~Mesh3dReader();
    
    Mesh* read(Resources* resources_, const std::string& filename_) const;
    
private:
    template <typename T>
    bool _readRawData(std::ifstream& file, T& data) const;
    std::string _readStrz(std::ifstream& file) const;
    Mesh* read_version_1(Resources* resources_, std::ifstream& file) const;
};

template <typename T>
bool Mesh3dReader::_readRawData(std::ifstream& file, T& data) const
{
    file.read(reinterpret_cast<char*>(&data), sizeof(T));
    return file.good();
}

ENGINE_NAMESPACE_END


#endif	/* MESH3DREADER_H */

