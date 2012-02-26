#ifndef _RESPTRS_TYPES_H_
#define _RESPTRS_TYPES_H_

#include "smart_ptr/smart_ptr.h"

#include "glbuffer/glbuffer.h"
typedef smart_ptr<GL::Buffer> buffer_ptr;

#include "glshader/glshader.h"
typedef smart_ptr<GL::VertexShader> vshader_ptr;
typedef smart_ptr<GL::FragmentShader> fshader_ptr;

#include "glprogram/glprogram.h"
typedef smart_ptr<GL::Program> program_ptr;

#include "gltexture/gltexture.h"
typedef smart_ptr<GL::Texture1D> texture1d_ptr;
typedef smart_ptr<GL::Texture2D> texture2d_ptr;
typedef smart_ptr<GL::Texture3D> texture3d_ptr;
typedef smart_ptr<GL::TextureCube> texturecube_ptr;
typedef smart_ptr<GL::TextureRect> texturerect_ptr;

#include "mesh/mesh.h"
typedef smart_ptr<Rage::Mesh> mesh_ptr;

#include "material/material.h"
typedef smart_ptr<Rage::Material> material_ptr;

#endif  //_RESPTRS_TYPES_H_
