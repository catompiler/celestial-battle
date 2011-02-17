#include "vfs.h"
#include "glmath/mat2.h"
//#include <cstdio>

/*
 * File
 */

VFS::File::File()
{
    _f = NULL;
}

VFS::File::~File()
{
    if(_f != NULL){
        close();
    }
}

bool VFS::File::open(const String& fn, IO::openmode_t om)
{
    char md[4] = {0};
    int i = 0;

    /*if(om & IO::File::OpenMode::Append){
        md[i++]='a';
        if(om & IO::File::OpenMode::Read){
            md[i++]='+';
        }
    }else{
        if(om & IO::File::OpenMode::Truncate ||
           om & IO::File::OpenMode::Write){
            md[i++]='w';
            if(om & IO::File::OpenMode::Read){
                md[i++]='+';
            }
        }else{
            md[i++]='r';
            if(om & IO::File::OpenMode::Write){
                md[i++]='+';
            }
        }
    }*/
// rwa+
    
    if(om & IO::OpenMode::Truncate){
        md[i++] = 'w';
        if(om & IO::OpenMode::Read){
            md[i++] = '+';
        }
    }else if(om & IO::OpenMode::Append){
        md[i++] = 'a';
        if(om & IO::OpenMode::Read){
            md[i++] = '+';
        }
    }else if(om & IO::OpenMode::Write){
        if(om & IO::OpenMode::Read){
            md[i++] = 'r';
            md[i++] = '+';
        }else{
            md[i++] = 'w';
        }
    }else{// if(om & IO::OpenMode::Read){
        md[i++] = 'r';
    }

    if(om & IO::OpenMode::Binary){
        md[i++]='b';
    }
    //fprintf(stdout,md);
    _f = ::fopen(fn.c_str(), md);

    return _f != NULL;
}

bool VFS::File::close()
{
    int res = ::fclose(_f);
    if(res == 0){
        _f = NULL;
        return true;
    }
    return false;
}

IO::datasize_t VFS::File::size()
{
    IO::offset_t old_pos = tell();

    if(seek(0, IO::SeekOrigin::End) == false){
        return 0;
    }
    
    IO::offset_t end_pos = tell();

    seek(old_pos, IO::SeekOrigin::Begin);

    return static_cast<IO::datasize_t>(end_pos);
}

bool VFS::File::seek(IO::offset_t p, IO::seekorigin_t o)
{
    int orgn = 0;
    switch(o){
        default:
        case IO::SeekOrigin::Begin:
            orgn = SEEK_SET;
            break;
        case IO::SeekOrigin::Current:
            orgn = SEEK_CUR;
            break;
        case IO::SeekOrigin::End:
            orgn = SEEK_END;
            break;
    }
    return ::fseek(_f, p, orgn) == 0;
}

IO::offset_t VFS::File::tell()
{
    return ::ftell(_f);
}

IO::datasize_t VFS::File::read(void* data, IO::datasize_t s)
{
    if(::fread(data, s, 1, _f) == 1){
        return s;
    }
    return 0;
}

IO::datasize_t VFS::File::write(const void* data, IO::datasize_t s)
{
    if(::fwrite(data, s, 1, _f) == 1){
        return s;
    }
    return 0;
}

bool VFS::File::ungetc(char c)
{
    return ::ungetc(c, _f) == c;
}


/*
 * VFS
 */

VFS::VFS() {
}

VFS::~VFS() {
}

