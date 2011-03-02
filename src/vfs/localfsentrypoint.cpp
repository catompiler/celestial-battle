#include "localfsentrypoint.h"
#include <fstream>



String LocalFSEntryPoint::separator()
{
    return
    #ifdef WIN32
    String("\\")
    #else
    String("/")
    #endif
    ;
}

LocalFSEntryPoint::LocalFSEntryPoint()
{
    _path = String();
}

LocalFSEntryPoint::LocalFSEntryPoint(const String& path_)
{
    _setPath(path_);
}

LocalFSEntryPoint::~LocalFSEntryPoint()
{
}

std::iostream* LocalFSEntryPoint::open(const String& fn, std::ios_base::openmode om)
{
    String res_path = _getSumPath(_path, fn);
    
    std::fstream* fst = new std::fstream;
    fst->open(res_path.c_str(), om);
    
    if(!(*fst)){
        delete fst;
        fst = NULL;
    }
    
    return fst;
}

void LocalFSEntryPoint::setPath(const String& path_)
{
    _setPath(path_);
}

const String& LocalFSEntryPoint::path()
{
    return _path;
}

void LocalFSEntryPoint::_setPath(const String& path_)
{
    String res = path_;
    
    String sep = separator();
    if(path_.right(1) != sep)res += sep;
    
    _path = res;
}

String LocalFSEntryPoint::_getSumPath(const String& path1_, const String& path2_)
{
    String res;
    
    //if(path1_.empty() || path2_.empty()) return res;
    
    String sep = separator();
    if(path1_.right(1) == sep){
        if(path2_.left(1) == sep){
            res = path1_ + path2_.right(path2_.length() - 1);
        }else{
            res = path1_ + path2_;
        }
    }else{
        if(path2_.left(1) == sep){
            res = path1_ + path2_;
        }else if(path1_.empty()){
            res = path2_;
        }else{
            res = path1_ + sep + path2_;
        }
    }
    
    return res;
}
