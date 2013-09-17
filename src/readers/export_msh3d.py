bl_info = {
    "name": "Export to Msh3D (*.msh3d)",
    "author": "artem.lab@gmail.com",
    "version": (1, 0),
    "blender": (2, 6, 3),
    "api": 36079,
    "location": "File > Export > Export to Msh3D (*.msh3d)",
    "description": "Export to Msh3D",
    "warning": "",
    "wiki_url": "",
    "tracker_url": "",
    "category": "Import-Export"
}


import bpy
# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.types import Operator
# struct for write binary files
import struct;


class Pair():
    first = None;
    second = None;
    
    def __init__(self):
        pass;
    def __init__(self, first_, second_):
        self.first = first_;
        self.second = second_;


class BaseExporter():
    
    def getSelectedObjects(context, type):
        objs = list();
        for obj in context.selected_objects:
            if(obj.type == type):
                objs.append(obj);
        return objs;
    
    def triangulateFace(points):
        l = len(points);
        if(l < 3):
            return None;
        res_verts = [];
        for n in range(0, l - 3 + 1):
            res_verts.append(points[0]);
            res_verts.append(points[n + 1]);
            res_verts.append(points[n + 2]);
        return res_verts;
    
    def searchValue(array, value, offset = 0):
        try:
            return array.index(value, offset);
        except ValueError:
            return -1;
    
    def isEqualVertex(vertex_l, vertex_r):
        return vertex_l == vertex_r;
    
    def getAttribsVertex(attribs, index):
        res_vertex = {};
        for name in attribs:
            values = attribs[name];
            res_vertex[name] = values[index];
        return res_vertex;
    
    def isEqualAttribsVertex(attribs, vertex, index):
        vertex_cmp = BaseExporter.getAttribsVertex(attribs, index);
        return BaseExporter.isEqualVertex(vertex_cmp, vertex);
    
    def searchEqualAttribsVertex(attribs, vertex):
        offset = 0;
        index = -1;
        keys = list(attribs.keys());
        if(len(keys) == 0):
            return index;
        key = keys[0];
        while(True):
            index = BaseExporter.searchValue(
                        attribs[key], vertex[key], offset);
            if(index == -1):
                break;
            offset = index + 1;
            if(BaseExporter.isEqualAttribsVertex(attribs, vertex, index)):
                break;
        return index;
    
    def appendAttribsVertex(attribs, vertex):
        for name in attribs:
            attribs[name].append(vertex[name]);
    
    def optimizeData(indices, attribs):
        res_indices = [];
        res_attribs = {};
        vertex = {};
        search_index = -1;
        cur_len = 0;
        for name in attribs.keys():
            res_attribs[name] = [];
            vertex[name] = [];
        for index in indices:
            vertex = BaseExporter.getAttribsVertex(attribs, index);
            search_index = BaseExporter.searchEqualAttribsVertex(
                                res_attribs, vertex);
            if(search_index == -1):
                res_indices.append(cur_len);
                cur_len = cur_len + 1;
                BaseExporter.appendAttribsVertex(res_attribs, vertex);
            else:
                res_indices.append(search_index);
        return Pair(res_indices, res_attribs);
    
    def writeStrz(file, str):
        bytes_data = bytes(str, 'utf-8');
        data = struct.pack("{0}s".format(len(bytes_data) + 1), bytes_data);
        file.write(data);
    
    def writeInt(file, i):
        data = struct.pack("I", i);
        file.write(data);
    
    def writeInt2(file, i0, i1):
        data = struct.pack("II", i0, i1);
        file.write(data);
    
    def writeInt3(file, i0, i1, i2):
        data = struct.pack("III", i0, i1, i2);
        file.write(data);
    
    def writeInt4(file, i0, i1, i2, i3):
        data = struct.pack("IIII", i0, i1, i2, i3);
        file.write(data);
    
    def writeFloat(file, f):
        data = struct.pack("f", f);
        file.write(data);
    
    def writeFloat2(file, f0, f1):
        data = struct.pack("ff", f0, f1);
        file.write(data);
    
    def writeFloat3(file, f0, f1, f2):
        data = struct.pack("fff", f0, f1, f2);
        file.write(data);
    
    def writeFloat4(file, f0, f1, f2, f3):
        data = struct.pack("ffff", f0, f1, f2, f3);
        file.write(data);


#
# Mesh3d file format
# 8 bytes 'mesh3d',0,0 magic
# 4 bytes version
# 4 bytes indices count
# ((indices count) * 4 byte) bytes indices
# 4 bytes attribs count
# strz attrib name
# 4 bytes components count
# 4 bytes count
# ((components count) * (count) * 4 byte) bytes attrib data
#

class Msh3dExporter(BaseExporter):
    
    class ExportSettings:
        export_indices = True;
        
        export_vertices = True;
        attrib_vertex_name = "in_vertex";
        
        export_normals = True;
        attrib_normal_name = "in_normal";
        
        export_texuvs = True;
        attrib_texuv_name = "in_texuv";
    
    
    _magic = b'mesh3d';
    _version = 1;
    
    def writeMagic(file):
        l = len(Msh3dExporter._magic);
        data = struct.pack("8s", Msh3dExporter._magic);
        file.write(data);
    
    def writeVersion(file):
        data = struct.pack("I", Msh3dExporter._version);
        file.write(data);
    
    def getIndices(self, context, mesh, settings):
        indices = [];
        for face in mesh.polygons:
            triangles = BaseExporter.triangulateFace(face.vertices);
            for index in triangles:
                indices.append(index);
        return indices;
    
    def getVertices(self, context, mesh, settings):
        vertices = [];
        for face in mesh.polygons:
            face_vertices = [];
            for index in face.vertices:
                face_vertices.append((mesh.vertices[index].co[0],
                                      mesh.vertices[index].co[1],
                                      mesh.vertices[index].co[2]));
            triangles = BaseExporter.triangulateFace(face_vertices);
            for vertex in triangles:
                vertices.append(vertex);
        return vertices;
    
    def getNormals(self, context, mesh, settings):
        normals = [];
        for face in mesh.polygons:
            face_normals = [];
            if(face.use_smooth):
                for index in face.vertices:
                    face_normals.append((mesh.vertices[index].normal[0],
                                         mesh.vertices[index].normal[1],
                                         mesh.vertices[index].normal[2]));
            else:
                for _ in range(0, len(face.vertices)):
                    face_normals.append((face.normal[0],
                                         face.normal[1],
                                         face.normal[2]));
            
            tr_normals = BaseExporter.triangulateFace(face_normals);
            for normal in tr_normals:
                normals.append(normal);
        return normals;
    
    def getTexuvs(self, context, mesh, settings):
        uvlayer = mesh.uv_layers.active;
        if(uvlayer == None):
            return None;
        texuvs = [];
        n = 0;
        for face in mesh.polygons:
            face_uvs = [];
            for _ in range(0,len(face.vertices)):
                face_uvs.append((uvlayer.data[n].uv[0], uvlayer.data[n].uv[1]));
                n = n + 1;
            tr_face_uvs = BaseExporter.triangulateFace(face_uvs);
            for uv in tr_face_uvs:
                texuvs.append(uv);
        return texuvs;
    
    def exportIndices(self, file, indices, settings):
        BaseExporter.writeInt(file, len(indices));
        for index in indices:
            BaseExporter.writeInt(file, index);
        return True;
    
    def exportAttrib(self, file, attrib_name, attrib_data, settings):
        comps_count = 0;
        if(len(attrib_data) != 0):
            comps_count = len(attrib_data[0]);
        BaseExporter.writeStrz(file, attrib_name);
        BaseExporter.writeInt(file, comps_count);
        BaseExporter.writeInt(file, len(attrib_data));
        for value in attrib_data:
            for component in value:
                BaseExporter.writeFloat(file, component);
        return True;
    
    def exportAttribs(self, file, attribs, settings):
        BaseExporter.writeInt(file, len(attribs));
        for name in attribs:
            self.exportAttrib(file, name, attribs[name], settings);
        return True;
    
    def exportMesh(self, context, file, mesh, settings):
        indices = [];
        attribs = {};
        
        if(settings.export_indices):
            mesh_indices = self.getIndices(context, mesh, settings);
            if(mesh_indices == None):
                print("Indices not found!");
                return False;
            for i in range(0, len(mesh_indices)):
                indices.append(i);
            print("Indices count:", len(indices));
        
        if(settings.export_vertices):
            vertices = self.getVertices(context, mesh, settings);
            if(vertices == None):
                print("Vertices not found!");
                return False;
            attribs[settings.attrib_vertex_name] = vertices;
            print("Vertices count:", len(vertices));
        
        if(settings.export_normals):
            normals = self.getNormals(context, mesh, settings);
            if(normals == None):
                print("Normals not found!");
                return False;
            attribs[settings.attrib_normal_name] = normals;
            print("Normals count:", len(normals));
        
        if(settings.export_texuvs):
            texuvs = self.getTexuvs(context, mesh, settings);
            if(texuvs == None):
                print("Texuvs not found!");
                return False;
            attribs[settings.attrib_texuv_name] = texuvs;
            print("Texuvs count:", len(texuvs));
        
        optimized = BaseExporter.optimizeData(indices, attribs);
        indices = optimized.first;
        attribs = optimized.second;
        #print(indices);
        #print(attribs);
        print("Optimization's results:");
        print("indices", ":", len(indices));
        for name in attribs:
            print(name, ":", len(attribs[name]));
        
        self.exportIndices(file, indices, settings);
        self.exportAttribs(file, attribs, settings);
        
        return True;
    
    def export(self, context, filepath, settings):
        print("Exporting msh3d...");
        
        objects = BaseExporter.getSelectedObjects(context, 'MESH');
        
        if(len(objects) != 1):
            return False;
        
        try:
            f = open(filepath, 'wb');
        except IOError:
            return False;
        
        Msh3dExporter.writeMagic(f);
        Msh3dExporter.writeVersion(f);
        
        object = objects[0];
        mesh = object.data;
        
        result = self.exportMesh(context, f, mesh, settings);
        
        f.close()
        print("done.");
        return result;



def operator_result(res):
    if(res):
        return {'FINISHED'};
    return {'CANCELLED'};

class ExportMsh3d(Operator, ExportHelper):
    '''Export selected object into *.msh3d file'''
    bl_idname = "export_msh3d.exporter"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_label = "Export *.msh3d"

    # ExportHelper mixin class uses this
    filename_ext = ".msh3d"

    filter_glob = StringProperty(
            default="*.msh3d",
            options={'HIDDEN'},
            )

    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before calling.
    
    # need indices
    export_indices = BoolProperty(
            name = "Indices",
            description = "Export indices",
            default = True
            )
    
    # need vertices
    export_vertices = BoolProperty(
            name = "Vertices",
            description = "Export vertices",
            default = True
            )
    attrib_vertex_name = StringProperty(
            name = "Name",
            description = "Attrib vertices name",
            default = "in_vertex"
            )
    
    # need normals
    export_normals = BoolProperty(
            name = "Normals",
            description = "Export normals",
            default = True
            )
    attrib_normal_name = StringProperty(
            name = "Name",
            description = "Attrib normals name",
            default = "in_normal"
            )
    
    # need texuvs
    export_texuvs = BoolProperty(
            name = "TexUVs",
            description = "Export texuvs",
            default = True
            )
    attrib_texuv_name = StringProperty(
            name = "Name",
            description = "Attrib texuvs name",
            default = "in_texuv"
            )

    def execute(self, context):
        
        objs = BaseExporter.getSelectedObjects(context, 'MESH');
        
        if(len(objs) == 0):
            print("no objects selected");
            return operator_result(False);
        
        if(len(objs) > 1):
            print("too many objects selected");
            return operator_result(False);
        
        settings = Msh3dExporter.ExportSettings();
        
        settings.export_indices = self.export_indices;
        
        settings.export_vertices = self.export_vertices;
        settings.attrib_vertex_name = self.attrib_vertex_name;
        
        settings.export_normals = self.export_normals;
        settings.attrib_normal_name = self.attrib_normal_name;
        
        settings.export_texuvs = self.export_texuvs;
        settings.attrib_texuv_name = self.attrib_texuv_name;
        
        exporter = Msh3dExporter();
        
        return operator_result(exporter.export(context, self.filepath, settings));


# Only needed if you want to add into a dynamic menu
def menu_func_export_msh3d(self, context):
    self.layout.operator(ExportMsh3d.bl_idname, text="Export Msh3D")


def register():
    bpy.utils.register_class(ExportMsh3d)
    bpy.types.INFO_MT_file_export.append(menu_func_export_msh3d)


def unregister():
    bpy.utils.unregister_class(ExportMsh3d)
    bpy.types.INFO_MT_file_export.remove(menu_func_export_msh3d)


if __name__ == "__main__":
    register()

    # test call
    # bpy.ops.export_msh3d.exporter('INVOKE_DEFAULT')
