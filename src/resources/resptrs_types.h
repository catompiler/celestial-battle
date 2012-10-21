#ifndef _RESPTRS_TYPES_H_
#define _RESPTRS_TYPES_H_

#include "resource_ptr.h"

#include "glbuffer/glbuffer.h"
typedef resource_ptr<GL::Buffer> buffer_ptr;

#include "glshader/glshader.h"
typedef resource_ptr<GL::VertexShader> vertex_shader_ptr;
typedef resource_ptr<GL::FragmentShader> fragment_shader_ptr;
typedef resource_ptr<GL::GeometryShader> geometry_shader_ptr;
typedef resource_ptr<GL::TessControlShader> tess_control_shader_ptr;
typedef resource_ptr<GL::TessEvalShader> tess_eval_shader_ptr;
typedef resource_ptr<GL::ComputeShader> compute_shader_ptr;

#include "glprogram/glprogram.h"
typedef resource_ptr<GL::Program> program_ptr;

#include "gltexture/gltexture.h"
typedef resource_ptr<GL::Texture> texture_ptr;
typedef resource_ptr<GL::Texture1D> texture1d_ptr;
typedef resource_ptr<GL::Texture2D> texture2d_ptr;
typedef resource_ptr<GL::Texture3D> texture3d_ptr;
typedef resource_ptr<GL::TextureCube> texturecube_ptr;
typedef resource_ptr<GL::TextureRect> texturerect_ptr;

#include "mesh/mesh.h"
typedef resource_ptr<Rage::Mesh> mesh_ptr;

#include "material/material.h"
typedef resource_ptr<Rage::Material> material_ptr;

#endif  //_RESPTRS_TYPES_H_
