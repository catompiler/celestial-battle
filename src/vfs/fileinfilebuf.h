#ifndef _FILEINFILEBUF_H_ 
#define _FILEINFILEBUF_H_

#include <iostream>
#include <fstream>

class fileinfilebuf
    :public std::basic_filebuf<char, std::char_traits<char> >
{
    typedef std::basic_filebuf<char, std::char_traits<char> > std_basic_filebuf;
    
public:
    fileinfilebuf(std::streampos start_ = 0, std::streampos end_ = -1);
    fileinfilebuf& setRange(std::streampos start_ = 0, std::streampos end_ = -1);
protected:
    std::streamsize showmanyc();

    int_type underflow();

    int_type uflow();
    
    int_type overflow(int_type __c = traits_type::eof());

    __streambuf_type* setbuf(char_type* __s, std::streamsize __n);

    pos_type seekoff(off_type __off, std::ios_base::seekdir __way,
            std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out);

    pos_type seekpos(pos_type __pos,
            std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out);

    std::streamsize xsgetn(char_type* __s, std::streamsize __n);

    std::streamsize xsputn(const char_type* __s, std::streamsize __n);
    
    int_type _underflow();
    
    std::streampos _start;
    std::streampos _end;
    bool _need_set_start;
    
};


#endif  //_FILEINFILEBUF_H_