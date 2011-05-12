#include "localfsentrypoint.h"
#include <fstream>
#include <algorithm>
#include <iterator>
//#include <iostream>

const std::string LocalFSEntryPoint::_separator = std::string(
#ifdef WIN32
    "\\"
#else
    "/"
#endif
);//end

const std::string& LocalFSEntryPoint::separator()
{
    return _separator;
}

LocalFSEntryPoint::LocalFSEntryPoint()
{
    _path = std::string();
}

LocalFSEntryPoint::LocalFSEntryPoint(const std::string& path_)
{
    _setPath(path_);
}

LocalFSEntryPoint::~LocalFSEntryPoint()
{
}

std::iostream* LocalFSEntryPoint::open(const std::string& fn, std::ios_base::openmode om) const
{
    std::string res_path = _addToPath(fn);
    
    std::fstream* fst = new std::fstream;
    fst->open(res_path.c_str(), om);
    
    if(!(*fst)){
        delete fst;
        fst = NULL;
    }
    
    return fst;
}

void LocalFSEntryPoint::setPath(const std::string& path_)
{
    _setPath(path_);
}

const std::string& LocalFSEntryPoint::path() const
{
    return _path;
}

void LocalFSEntryPoint::_setPath(const std::string& path_)
{
    //if path_ can contain separator
    if(path_.length() >= _separator.length()){
        //find it
        std::string::const_iterator it = std::find_end(path_.begin(), path_.end(),
                                                _separator.begin(), _separator.end());
        //if separator not found
        if(it == path_.end() ||
            //or found not at the end
            static_cast<unsigned int>(std::distance(it, path_.end())) > _separator.length()){
            //append separator
            _path = path_ + _separator;
        }
    }else{
        _path = path_ + _separator;
    }
}

std::string LocalFSEntryPoint::_addToPath(const std::string& fn) const
{
    std::string res = _path;
    
    //if fn beginning from separator
    if(fn.length() >= _separator.length() &&
            std::equal(_separator.begin(), _separator.end(), fn.begin())){
        
        //get iterator after separator
        std::string::const_iterator it = fn.begin();
        std::advance(it, _separator.length());
        
        //copy fn without separator to res
        std::copy(it, fn.end(), std::back_inserter(res));
    }else{
        res += fn;
    }
    
    return res;
}
