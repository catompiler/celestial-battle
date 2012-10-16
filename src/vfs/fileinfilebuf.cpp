#include "fileinfilebuf.h"

//#define FINF_DEBUG

fileinfilebuf::fileinfilebuf(std::streampos start_, std::streampos end_)
        :std_basic_filebuf(){
    _start = start_;
    _end = end_;
    _need_set_start = true;
}

fileinfilebuf& fileinfilebuf::setRange(std::streampos start_, std::streampos end_){
    
    if(is_open() == false || _need_set_start == true){
        _start = start_;
        _end = end_;
        _need_set_start = true;
    }
    
    return *this;
}

std::streamsize fileinfilebuf::showmanyc(){
    #ifdef FINF_DEBUG
    std::cout << " showmanyc() ";
    #endif
    return std_basic_filebuf::showmanyc();
}

fileinfilebuf::int_type fileinfilebuf::underflow(){
    #ifdef FINF_DEBUG
    std::cout << " underflow() ";
    #endif
    //return std_basic_filebuf::underflow();
    return _underflow();
}

fileinfilebuf::int_type fileinfilebuf::uflow(){
    #ifdef FINF_DEBUG
    std::cout << " uflow() ";
    #endif
    return std_basic_filebuf::uflow();
}

fileinfilebuf::int_type fileinfilebuf::overflow(int_type __c){
    #ifdef FINF_DEBUG
    std::cout << " overflow() ";
    #endif
    return -1;//std_basic_filebuf::overflow(__c);
}

fileinfilebuf::__streambuf_type* fileinfilebuf::setbuf(char_type* __s, std::streamsize __n){
    #ifdef FINF_DEBUG
    std::cout << " setbuf() ";
    #endif
    return std_basic_filebuf::setbuf(__s, __n);
}


fileinfilebuf::pos_type fileinfilebuf::seekoff(off_type __off, std::ios_base::seekdir __way,
        std::ios_base::openmode __mode){
    pos_type file_pos = 0;
    switch(__way){
        case std::ios_base::beg:
            #ifdef FINF_DEBUG
            std::cout << " seekoff(" << __off << ", beg)";
            #endif
            __off += _start;
            break;
        case std::ios_base::cur:
            #ifdef FINF_DEBUG
            std::cout << " seekoff(" << __off << ", cur)";
            #endif
            file_pos = std_basic_filebuf::seekoff(0,
                                    std::ios_base::cur, __mode);
            __way = std::ios_base::beg;
            __off += file_pos;
            if(_need_set_start){
                __off += _start;
            }
            break;
        case std::ios_base::end:
            #ifdef FINF_DEBUG
            std::cout << " seekoff(" << __off << ", end)";
            #endif
            if(_end != static_cast<std::streampos>(-1)){
                __way = std::ios_base::beg;
                __off = _end + __off;
            }
            break;
    }

    if(__off < _start) __off = _start;
    else{
        if(__mode & std::ios_base::in){
            if(__off > _end) __off = _end;
        }
    }
    
    #ifdef FINF_DEBUG
    std::cout << " new offset: " << __off << " ";
    #endif

    pos_type res = std_basic_filebuf::seekoff(__off, __way, __mode);
    if(res > 0){
        res -= _start;
        _need_set_start = false;
    }

    return res;
}

fileinfilebuf::pos_type fileinfilebuf::seekpos(pos_type __pos,
        std::ios_base::openmode __mode){
    __pos += _start;
    if(__pos < _start) __pos = _start;
    else{
        if(__mode & std::ios_base::in){
            if(__pos > _end) __pos = _end;
        }
    }
    #ifdef FINF_DEBUG
    std::cout << " seekpos(" << __pos << ") ";
    #endif
    
    pos_type res = std_basic_filebuf::seekpos(__pos, __mode);
    if(res > 0) res -= _start;

    return res;
}

std::streamsize fileinfilebuf::xsgetn(char_type* __s, std::streamsize __n){
    #ifdef FINF_DEBUG
    std::cout << " xsgetn(" << __n << ") ";
    #endif
    return std_basic_filebuf::xsgetn(__s, __n);
}

std::streamsize fileinfilebuf::xsputn(const char_type* __s, std::streamsize __n){
    #ifdef FINF_DEBUG
    std::cout << " xsputn(" << __n << ") ";
    #endif
    return std_basic_filebuf::xsputn(__s, __n);
}

fileinfilebuf::int_type fileinfilebuf::_underflow(){

    pos_type file_pos = std_basic_filebuf::seekoff(0,
                            std::ios_base::cur, std::ios_base::in);
    if(_need_set_start){
        file_pos += _start;
        _need_set_start = false;
        std_basic_filebuf::seekoff(file_pos,
                            std::ios_base::beg, std::ios_base::in);
    }

    size_t before_end = _end - file_pos;
    size_t buf_len = _M_buf_size > 0 ? _M_buf_size - 1 : 1;
    size_t len = before_end > buf_len ? buf_len : before_end;

    
    std::streamsize n = _M_file.xsgetn(eback(), len);
    #ifdef FINF_DEBUG
    std::cout << "readed: " << n << std::endl;
    #endif
    if(n > 0){
        setg(eback(), eback(), eback() + n);
        return traits_type::to_int_type(*eback());
    }
    return traits_type::eof();//to_int_type(EOF);
}




