#include "utf8string.h"
#include <string.h>
#include <locale>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

size_t utf8string::utf8char::size(const char* c)
{
    size_t res = 0;
    unsigned char _c = c[0];
    
    while(_c & 0x80){
        res ++;
        _c <<= 0x1;
    }
    
    return res == 0 ? 1 : res;
}

size_t utf8string::utf8char::size(unsigned int c)
{
    if(c > 0x001fffff) return 0;
    
    if(c >= 0x00010000) return 4;
    if(c >= 0x00000800) return 3;
    if(c >= 0x00000080) return 2;
    
    return 1;
}
/*
   0000 0000-0000 007F   0xxxxxxx
   0000 0080-0000 07FF   110xxxxx 10xxxxxx
   0000 0800-0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx
   0001 0000-001F FFFF   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 */
unsigned int utf8string::utf8char::decode(const char* c)
{
    unsigned int res = 0;
    size_t s = size(c);

    switch(s){
        case 1:
        default:
            res=static_cast<unsigned int>(*c);
            break;
        case 2:
            res = (res | (c[0] & 0x1f)) << 6;
            res = (res | (c[1] & 0x3f));
            break;
        case 3:
            res = (res | (c[0] & 0xf )) << 6;
            res = (res | (c[1] & 0x3f)) << 6;
            res = (res | (c[2] & 0x3f));
            break;
        case 4:
            res = (res | (c[0] & 0x7 )) << 6;
            res = (res | (c[1] & 0x3f)) << 6;
            res = (res | (c[2] & 0x3f)) << 6;
            res = (res | (c[3] & 0x3f));
            break;
    }
    
    return res;
}

size_t utf8string::utf8char::encode(char* uc, unsigned int c)
{
    size_t s = size(c);
    
    switch(s){
        case 1:
        default:
            *uc = static_cast<char>(c);
            break;
        case 2://0x1f 0x3f <<6
            uc[0] = static_cast<char>(((c >> 6 )         | 0xc0));
            uc[1] = static_cast<char>(((c      ) & 0x3f) | 0x80);
            break;
        case 3://0xf
            uc[0] = static_cast<char>(((c >> 12)         | 0xe0));
            uc[1] = static_cast<char>(((c >> 6 ) & 0x3f) | 0x80);
            uc[2] = static_cast<char>(((c      ) & 0x3f) | 0x80);
            break;
        case 4://0x7
            uc[0] = static_cast<char>(((c >> 18)         | 0xf0));
            uc[1] = static_cast<char>(((c >> 12) & 0x3f) | 0x80);
            uc[2] = static_cast<char>(((c >> 6 ) & 0x3f) | 0x80);
            uc[3] = static_cast<char>(((c      ) & 0x3f) | 0x80);
            break;
    }
    
    return s;
}

bool utf8string::utf8char::validate(const char* c)
{
    size_t s = size(c);
    
    if(s > 4) return false;
    
    switch(s){
        case 1:
            if(c[0] & 0x80) return false;
            break;
        case 2:
            if((c[0] & 0xe0) != 0xc0) return false;
            if((c[1] & 0xc0) != 0x80) return false;
            break;
        case 3:
            if((c[0] & 0xf0) != 0xe0) return false;
            if((c[1] & 0xc0) != 0x80) return false;
            if((c[2] & 0xc0) != 0x80) return false;
            break;
        case 4:
            if((c[0] & 0xf8) != 0xf0) return false;
            if((c[1] & 0xc0) != 0x80) return false;
            if((c[2] & 0xc0) != 0x80) return false;
            if((c[3] & 0xc0) != 0x80) return false;
            break;
        default:
            return false;
    }
    
    return true;
}



/*
 *	utf8string_rep
 */

utf8string::utf8string_rep::utf8string_rep()
{
    _links_count = 1;
    _data = new utf8string_impl();
}

utf8string::utf8string_rep::utf8string_rep(utf8string_rep* src)
{
    _links_count = 1;
    _data = new utf8string_impl(*src->_data);
}

utf8string::utf8string_rep::utf8string_rep(utf8string_impl* src)
{
    _links_count = 1;
    _data = src;
}

utf8string::utf8string_rep::utf8string_rep(const utf8string_rep* src)
{
    _links_count = 1;
    _data = new utf8string_impl(*src->_data);
}

utf8string::utf8string_rep::utf8string_rep(const utf8string_impl* src)
{
    _links_count = 1;
    _data = new utf8string_impl(*src);
}

utf8string::utf8string_rep::~utf8string_rep()
{
    release();
}

bool utf8string::utf8string_rep::release()
{
    if(_links_count > 1){
        _links_count --;
        return false;
    }else if(_links_count == 1){
        _links_count = 0;
        delete _data;
        _data = NULL;
    }
    return true;
}



/*
 *	utf8string
 */

utf8string::utf8string()
{
    _rep = new utf8string_rep;
}

utf8string::utf8string(utf8string& src)
{
    src._rep->_links_count ++;
    _rep = src._rep;
}

utf8string::utf8string(const utf8string& src)
{
    _rep = new utf8string_rep(src._rep);
}

utf8string::utf8string(const char* src)
{
    _rep = new utf8string_rep(new utf8string_impl(src));
}

utf8string::utf8string(utf8string_impl& src)
{
    _rep = new utf8string_rep(&src);
}

utf8string::~utf8string()
{
    if(_rep->release()) delete _rep;
}

utf8string::utf8string_rep* utf8string::_modify_rep(utf8string_rep*& rep)
{
    if(rep->_links_count > 1){
        rep->_links_count --;
        rep = new utf8string_rep(rep);
    }
    return rep;
}

const char* utf8string::c_str() const
{
    return _rep->_data->c_str();
}

size_t utf8string::length() const
{
    return _rep->_data->length();
}

size_t utf8string::size() const
{
    return _rep->_data->size();
}


unsigned int utf8string::at(int n) const
{
    return _rep->_data->at(n);
}


bool utf8string::equal(const utf8string& src) const
{
    return _rep->_data->equal(*src._rep->_data);
}

bool utf8string::equal(const char* src) const
{
    return _rep->_data->equal(src);
}

bool utf8string::less(const utf8string& src) const
{
    return _rep->_data->less(*src._rep->_data);
}

bool utf8string::less(const char* src) const
{
    return _rep->_data->less(src);
}

bool utf8string::empty() const
{
    return _rep->_data->empty();
}

utf8string& utf8string::clear()
{
    _modify_rep(_rep);
    _rep->_data->clear();
    
    return *this;
}

utf8string& utf8string::set(utf8string& src)
{
    if(_rep->release()) delete _rep;
    src._rep->_links_count ++;
    _rep = src._rep;
    
    return *this;
}

utf8string& utf8string::set(const utf8string& src)
{
    if(_rep->release()) delete _rep;
    _rep = new utf8string_rep(src._rep);
    
    return *this;
}

utf8string& utf8string::set(const char* src)
{
    if(_rep->release()) delete _rep;
    _rep = new utf8string_rep(new utf8string_impl(src));
    
    return *this;
}

utf8string& utf8string::append(const utf8string& src)
{
    _modify_rep(_rep);
    _rep->_data->append(*src._rep->_data);
    
    return *this;
}

utf8string& utf8string::append(const char* src)
{
    _modify_rep(_rep);
    _rep->_data->append(src);
    
    return *this;
}

utf8string& utf8string::prepend(const utf8string& src)
{
    _modify_rep(_rep);
    _rep->_data->prepend(*src._rep->_data);
    
    return *this;
}

utf8string& utf8string::prepend(const char* src)
{
    _modify_rep(_rep);
    _rep->_data->prepend(src);
    
    return *this;
}

utf8string& utf8string::insert(const utf8string& src, size_t npos)
{
    _modify_rep(_rep);
    _rep->_data->insert(*src._rep->_data, npos);
    
    return *this;
}

utf8string& utf8string::insert(const char* src, size_t npos)
{
    _modify_rep(_rep);
    _rep->_data->insert(src, npos);
    
    return *this;
}

int utf8string::indexOf(const utf8string& src) const
{
    return _rep->_data->indexOf(*src._rep->_data);
}

int utf8string::indexOf(const char* src) const
{
    return _rep->_data->indexOf(src);
}

int utf8string::lastindexOf(const utf8string& src) const
{
    return _rep->_data->lastindexOf(*src._rep->_data);
}

int utf8string::lastindexOf(const char* src) const
{
    return _rep->_data->lastindexOf(src);
}

utf8string& utf8string::replace(const utf8string& str, const utf8string& dst)
{
    _modify_rep(_rep);
    _rep->_data->replace(*str._rep->_data, *dst._rep->_data);
    
    return *this;
}

utf8string& utf8string::replace(const char* str, const char* dst)
{
    _modify_rep(_rep);
    _rep->_data->replace(str, dst);
    
    return *this;
}

utf8string& utf8string::replaceAll(const utf8string& str, const utf8string& dst)
{
    _modify_rep(_rep);
    _rep->_data->replaceAll(*str._rep->_data, *dst._rep->_data);
    
    return *this;
}

utf8string& utf8string::replaceAll(const char* str, const char* dst)
{
    _modify_rep(_rep);
    _rep->_data->replaceAll(str, dst);
    
    return *this;
}


utf8string utf8string::left(size_t n) const
{
    utf8string_impl* impl = new utf8string_impl(_rep->_data->left(n));
    utf8string res(*impl);
    
    return res;
}

utf8string utf8string::mid(size_t npos, size_t n) const
{
    utf8string_impl* impl = new utf8string_impl(_rep->_data->mid(npos,n));
    utf8string res(*impl);
    
    return res;
}

utf8string utf8string::right(size_t n) const
{
    utf8string_impl* impl = new utf8string_impl(_rep->_data->right(n));
    utf8string res(*impl);
    
    return res;
}


utf8string& utf8string::toUpper()
{
    _modify_rep(_rep);
    _rep->_data->toUpper();
    
    return *this;
}

utf8string& utf8string::toLower()
{
    _modify_rep(_rep);
    _rep->_data->toLower();
    
    return *this;
}


utf8string& utf8string::remove(size_t npos, size_t n)
{
    _modify_rep(_rep);
    _rep->_data->remove(npos, n);
    
    return *this;
}

utf8string& utf8string::remove(const utf8string& src)
{
    _modify_rep(_rep);
    _rep->_data->remove(*src._rep->_data);
    
    return *this;
}

utf8string& utf8string::remove(const char* src)
{
    _modify_rep(_rep);
    _rep->_data->remove(src);
    
    return *this;
}

utf8string& utf8string::removeAll(const utf8string& src)
{
    _modify_rep(_rep);
    _rep->_data->removeAll(*src._rep->_data);
    
    return *this;
}

utf8string& utf8string::removeAll(const char* src)
{
    _modify_rep(_rep);
    _rep->_data->removeAll(src);
    
    return *this;
}


utf8string& utf8string::format(const char* fmt, ...)
{
    char buf[utf8string_impl::max_format_buffer_size];
    ::va_list vl;
    
    ::va_start(vl, fmt);
    int res = ::vsprintf(buf, fmt, vl);
    ::va_end(vl);
    if(res){
        if(_rep->release())delete _rep;
        _rep = new utf8string_rep(new utf8string_impl(buf));
    }
    
    return *this;
}

int utf8string::toInt(bool* isOk) const
{
    return _rep->_data->toInt(isOk);
}

int utf8string::toInt(int base, bool* isOk) const
{
    return _rep->_data->toInt(base, isOk);
}

unsigned int utf8string::toUint(bool* isOk) const
{
    return _rep->_data->toUint(isOk);
}

unsigned int utf8string::toUint(int base, bool* isOk) const
{
    return _rep->_data->toUint(base, isOk);
}

float utf8string::toFloat(bool* isOk) const
{
    return _rep->_data->toFloat(isOk);
}

double utf8string::toDouble(bool* isOk) const
{
    return _rep->_data->toDouble(isOk);
}


utf8string& utf8string::setNum(int n)
{
    _modify_rep(_rep);
    _rep->_data->setNum(n);
    
    return *this;
}

utf8string& utf8string::setNum(unsigned int n)
{
    _modify_rep(_rep);
    _rep->_data->setNum(n);
    
    return *this;
}

utf8string& utf8string::setNum(float n)
{
    _modify_rep(_rep);
    _rep->_data->setNum(n);
    
    return *this;
}

utf8string& utf8string::setNum(double n)
{
    _modify_rep(_rep);
    _rep->_data->setNum(n);
    
    return *this;
}


utf8string utf8string::number(int n)
{
    utf8string_impl* impl = new utf8string_impl(utf8string_impl::number(n));
    utf8string res(*impl);
    
    return res;
}

utf8string utf8string::number(unsigned int n)
{
    utf8string_impl* impl = new utf8string_impl(utf8string_impl::number(n));
    utf8string res(*impl);
    
    return res;
}

utf8string utf8string::number(float n)
{
    utf8string_impl* impl = new utf8string_impl(utf8string_impl::number(n));
    utf8string res(*impl);
    
    return res;
}

utf8string utf8string::number(double n)
{
    utf8string_impl* impl = new utf8string_impl(utf8string_impl::number(n));
    utf8string res(*impl);
    
    return res;
}


utf8string& utf8string::operator=(const char* src)
{
    _modify_rep(_rep);
    _rep->_data->operator=(src);
    
    return *this;
}

utf8string& utf8string::operator=(const utf8string& src)
{
    _modify_rep(_rep);
    _rep->_data->operator=(*src._rep->_data);
    
    return *this;
}


bool utf8string::operator==(const char* src) const
{
    return _rep->_data->operator==(src);
}

bool utf8string::operator==(const utf8string& src) const
{
    return _rep->_data->operator==(*src._rep->_data);
}


bool utf8string::operator!=(const char* src) const
{
    return !_rep->_data->operator==(src);
}

bool utf8string::operator!=(const utf8string& src) const
{
    return !_rep->_data->operator==(*src._rep->_data);
}


bool utf8string::operator<(const char* src) const
{
    return _rep->_data->operator<(src);
}

bool utf8string::operator<(const utf8string& src) const
{
    return _rep->_data->operator<(*src._rep->_data);
}


utf8string& utf8string::operator+=(const char* src)
{
    _modify_rep(_rep);
    _rep->_data->operator+=(src);
    
    return *this;
}

utf8string& utf8string::operator+=(const utf8string& src)
{
    _modify_rep(_rep);
    _rep->_data->operator+=(*src._rep->_data);
    
    return *this;
}


utf8string utf8string::operator+(const char* src) const
{
    utf8string_impl* impl = new utf8string_impl(_rep->_data->operator+(src));
    utf8string res(*impl);
    
    return res;
}

utf8string utf8string::operator+(const utf8string& src) const
{
    utf8string_impl* impl = new utf8string_impl(_rep->_data->operator+(*src._rep->_data));
    utf8string res(*impl);
    
    return res;
}


unsigned int utf8string::operator[](int n) const
{
    return _rep->_data->operator[](n);
}



/*
 *	_impl
 */

size_t utf8string::utf8string_impl::length(const char* src)
{
    size_t i = 0;
    size_t len = 0;
    for(;;){
        if(src[i] == 0) break;
        i += utf8char::size(&src[i]);
        len ++;
    }
    return len;
}

size_t utf8string::utf8string_impl::size(const char* src)
{
    return ::strlen(src);
}

size_t utf8string::utf8string_impl::size(const char* src, size_t n)
{
    size_t i = 0;
    size_t ci = 0;
    
    for(;;){
        if(src[i] == 0) break;
        if(ci == n){
            break;
        }
        i += utf8char::size(&src[i]);
        ci ++;
    }
    return i;
}

unsigned int utf8string::utf8string_impl::at(const char* src, int n)
{
    const char* res_str = src + size(src, n);
    unsigned int res = utf8char::decode(res_str);
    
    return res;
}

char* utf8string::utf8string_impl::str_skip(char* src, size_t n)
{
    char* res = src + size(src, n);
    
    return res;
}

const char* utf8string::utf8string_impl::str_skip(const char* src, size_t n)
{
    const char* res = src + size(src, n);
    
    return res;
}

char* utf8string::utf8string_impl::str_alloc(size_t s)
{
    char* res = new char[s + 1];
    res[s] = 0x0;
    
    return res;
}

void utf8string::utf8string_impl::str_free(char* & src)
{
    delete[] src;
    src = NULL;
}

char* utf8string::utf8string_impl::str_copy(char* dst, const char* src)
{
    return ::strcpy(dst, src);
}

char* utf8string::utf8string_impl::str_copy(char* dst, const char* src, size_t s)
{
    return ::strncpy(dst, src, s);
}

char* utf8string::utf8string_impl::str_ncopy(char* dst, const char* src, size_t n)
{
    return ::strncpy(dst,src,size(src, n));
}

char* utf8string::utf8string_impl::str_copy(const char* src)
{
    size_t s = size(src);
    char* res = str_alloc(s);
    
    return str_copy(res, src, s);
}

char* utf8string::utf8string_impl::str_realloc(char*& src, size_t s, size_t src_d, size_t src_s)
{
    char* res = str_alloc(s);
    if(src_s == 0) src_s = size(src);
    
    str_copy(res, src + src_d, src_s);
    
    str_free(src);
    
    src = res;
    
    return res;
}

bool utf8string::utf8string_impl::str_equal(const char* src, const char* dst)
{
    return strcmp(src, dst) == 0;
}

bool utf8string::utf8string_impl::str_empty(const char* src)
{
    return src[0] == 0x0;
}

bool utf8string::utf8string_impl::str_less(const char* src, const char* dst)
{
    for(;*src != 0 && *dst != 0; ++src, ++dst){
        if(*src < *dst) return true;
    }
    return (*src == 0 && *dst != 0);
}

char* utf8string::utf8string_impl::str_clear(char*& src)
{
    if(str_empty(src))  return src;
    str_free(src);
    src = str_alloc(0);

    return src;
}

char* utf8string::utf8string_impl::str_append(const char* src, const char* dst)
{
    size_t src_s = size(src);
    size_t dst_s = size(dst);
    
    char* res = str_alloc(src_s + dst_s);
    
    str_copy(res, src);
    str_copy(res + src_s, dst);
    
    return res;
}

char* utf8string::utf8string_impl::str_prepend(const char* src, const char* dst)
{
    size_t src_s = size(src);
    size_t dst_s = size(dst);
    
    char* res = str_alloc(src_s + dst_s);
    
    str_copy(res, dst);
    str_copy(res + dst_s, src);
    
    return res;
}

char* utf8string::utf8string_impl::str_insert(const char* src, const char* dst, size_t npos)
{
    size_t src_s = size(src);
    size_t dst_s = size(dst);
    size_t pos = size(src, npos);
    
    char* res = str_alloc(src_s + dst_s);
    
    str_copy(res, src, pos);
    str_copy(res + pos, dst);
    str_copy(res + pos + dst_s, src + pos);
    
    return res;
}

char* utf8string::utf8string_impl::str_find(char* src, const char* dst)
{
    return strstr(src, dst);
}

const char* utf8string::utf8string_impl::str_find(const char* src, const char* dst)
{
    return strstr(src, dst);
}

int utf8string::utf8string_impl::str_indexof(const char* src, const char* dst)
{
    const char* str = str_find(src, dst);
    int res = str == NULL ? -1 : str - src;
    
    return res;
}

int utf8string::utf8string_impl::str_lastindexof(const char* src, const char* dst)
{
    const char* str = str_find(src, dst);
    const char* last_str = str;
    
    while(str != NULL){
        last_str = str;
        str = str_find(str, dst);
    }
    
    int res = last_str == NULL ? -1 : last_str - src;
    
    return res;
}

char* utf8string::utf8string_impl::str_replace(const char* src, const char* str, const char* dst)
{
    const char* find_res = str_find(src, str);
    if(find_res == NULL){
        return NULL;
    }
    
    size_t src_s = size(src);
    size_t dst_s = size(dst);
    size_t str_s = size(str);
    size_t pos = find_res - src;
    
    char* res = str_alloc(src_s - str_s + dst_s);
    
    str_copy(res, src, pos);
    str_copy(res + pos, dst);
    str_copy(res + pos + dst_s, src + pos + str_s);
    
    return res;
}

char* utf8string::utf8string_impl::str_replaceall(const char* src, const char* str, const char* dst)
{
    char* res = NULL;
    char* res_replace = str_replace(src, str, dst);
    
    while(res_replace != NULL){
        res = res_replace;
        
        res_replace = str_replace(res_replace, str, dst);
        if(res_replace != NULL){
            str_free(res);
        }
    }
    
    return res;
}

char* utf8string::utf8string_impl::str_remove(const char* src, size_t npos, size_t n)
{
    size_t src_s = size(src);
    size_t src_l = length(src);
    size_t dst_npos = src_l >= npos ? npos : src_l;
    size_t dst_n = src_l >= (npos + n) ? n : src_l >= npos ? src_l - npos : 0;
    const char* src_skip = str_skip(src, dst_npos);
    const char* src_skip_skip = str_skip(src_skip, dst_n);
    size_t dst_s_npos = src_skip - src;
    size_t dst_s_end  = src + src_s - src_skip_skip;
    size_t dst_s = dst_s_npos + dst_s_end;
    char* res = str_alloc(dst_s);
    
    str_copy(res, src, dst_s_npos);
    str_copy(res + dst_s_npos, src_skip_skip, dst_s_end);
    
    return res;
}

char* utf8string::utf8string_impl::str_remove(const char* src, const char* dst)
{
    const char* find_res = str_find(src, dst);
    if(find_res == NULL){
        return NULL;
    }
    
    size_t src_s = size(src);
    size_t dst_s = size(dst);
    size_t pos = find_res - src;
    
    char* res = str_alloc(src_s - dst_s);
    
    str_copy(res, src, pos);
    str_copy(res + pos, src + pos + dst_s);
    
    return res;
}

char* utf8string::utf8string_impl::str_removeall(const char* src, const char* dst)
{
    char* res = NULL;
    char* res_remove = str_remove(src, dst);
    
    while(res_remove != NULL){
        res = res_remove;
        
        res_remove = str_remove(res_remove, dst);
        if(res_remove != NULL){
            str_free(res);
        }
    }
    
    return res;
}

char* utf8string::utf8string_impl::str_left(const char* src, size_t n)
{
    size_t s = size(src,n);
    char* res = str_alloc(s);
    
    str_copy(res, src, s);
    
    return res;
}

char* utf8string::utf8string_impl::str_mid(const char* src, size_t npos, size_t n)
{
    const char* skip_src = str_skip(src, npos);
    size_t s = size(skip_src, n);
    char* res = str_alloc(s);
    
    str_copy(res, skip_src, s);
    
    return res;
}

char* utf8string::utf8string_impl::str_right(const char* src, size_t n)
{
    size_t l = length(src);
    size_t nl = n >= l ? l : l - n;
    const char* skip_src = str_skip(src, nl);
    size_t s = size(skip_src);
    char* res = str_alloc(s);
    
    str_copy(res, skip_src);
    
    return res;
}

char* utf8string::utf8string_impl::str_toupper(char* src)
{
    size_t i = 0;
    size_t src_c_s = 0;
    size_t dst_c_s = 0;
    
    wchar_t c = 0;
    
    std::locale loc("");
    
    for(;;){
        if(src[i] == 0) break;
        
        src_c_s = utf8char::size(&src[i]);
        
        if(src_c_s > sizeof(wchar_t)) break;
        
        c = static_cast<wchar_t>(utf8char::decode(&src[i]));
        try{
            c = std::toupper(c,loc);
        }catch(...){
            break;
        }
        
        dst_c_s = utf8char::size(static_cast<unsigned int>(c));
        
        if(dst_c_s != src_c_s) break;
        
        utf8char::encode(&src[i], c);
        
        i += utf8char::size(&src[i]);
    }
    
    return &src[i];
}

char* utf8string::utf8string_impl::str_tolower(char* src)
{
    size_t i = 0;
    size_t src_c_s = 0;
    size_t dst_c_s = 0;
    
    wchar_t c = 0;
    
    std::locale loc("");
    
    for(;;){
        if(src[i] == 0) break;
        
        src_c_s = utf8char::size(&src[i]);
        
        if(src_c_s > sizeof(wchar_t)) break;
        
        c = static_cast<wchar_t>(utf8char::decode(&src[i]));
        try{
            c = std::tolower(c,loc);
        }catch(...){
            break;
        }
        
        dst_c_s = utf8char::size(static_cast<unsigned int>(c));
        
        if(dst_c_s != src_c_s) break;
        
        utf8char::encode(&src[i], c);
        
        i += utf8char::size(&src[i]);
    }
    
    return &src[i];
}


utf8string::utf8string_impl::utf8string_impl()
{
    _chars = str_alloc(0);
}

utf8string::utf8string_impl::utf8string_impl(const utf8string_impl& src)
{
    _chars = str_copy(src._chars);
}

utf8string::utf8string_impl::utf8string_impl(const char* src)
{
    _chars = str_copy(src);
}

utf8string::utf8string_impl::~utf8string_impl()
{
    str_free(_chars);
}

const char* utf8string::utf8string_impl::c_str() const
{
    return _chars;
}

size_t utf8string::utf8string_impl::length() const
{
    return length(_chars);
}

size_t utf8string::utf8string_impl::size() const
{
    return size(_chars);
}

unsigned int utf8string::utf8string_impl::at(int n) const
{
    return at(_chars, n);
}

bool utf8string::utf8string_impl::equal(const utf8string_impl& src) const
{
    return str_equal(_chars, src._chars);
}

bool utf8string::utf8string_impl::equal(const char* src) const
{
    return str_equal(_chars, src);
}

bool utf8string::utf8string_impl::empty() const
{
    return str_empty(_chars);
}

bool utf8string::utf8string_impl::less(const utf8string_impl& src) const
{
    return str_less(_chars, src._chars);
}

bool utf8string::utf8string_impl::less(const char* src) const
{
    return str_less(_chars, src);
}

utf8string::utf8string_impl& utf8string::utf8string_impl::clear()
{
    str_clear(_chars);

    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::set(const utf8string_impl& src)
{
    str_free(_chars);
    _chars = str_copy(src._chars);
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::set(const char* src)
{
    str_free(_chars);
    _chars = str_copy(src);
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::append(const utf8string_impl& src)
{
    char* res = str_append(_chars, src._chars);
    
    str_free(_chars);
    _chars = res;
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::append(const char* src)
{
    char* res = str_append(_chars, src);
    
    str_free(_chars);
    _chars = res;
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::prepend(const utf8string_impl& src)
{
    char* res = str_prepend(_chars, src._chars);
    
    str_free(_chars);
    _chars = res;
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::prepend(const char* src)
{
    char* res = str_prepend(_chars, src);
    
    str_free(_chars);
    _chars = res;
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::insert(const utf8string_impl& src, size_t npos)
{
    char* res = str_insert(_chars, src._chars, npos);
    
    str_free(_chars);
    _chars = res;
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::insert(const char* src, size_t npos)
{
    char* res = str_insert(_chars, src, npos);
    
    str_free(_chars);
    _chars = res;
    
    return *this;
}

int utf8string::utf8string_impl::indexOf(const utf8string_impl& src) const
{
    return str_indexof(_chars, src._chars);
}

int utf8string::utf8string_impl::indexOf(const char* src) const
{
    return str_indexof(_chars, src);
}

int utf8string::utf8string_impl::lastindexOf(const utf8string_impl& src) const
{
    return str_lastindexof(_chars, src._chars);
}

int utf8string::utf8string_impl::lastindexOf(const char* src) const
{
    return str_lastindexof(_chars, src);
}

utf8string::utf8string_impl& utf8string::utf8string_impl::replace(const utf8string_impl& str, const utf8string_impl& dst)
{
    char* res = str_replace(_chars, str._chars, dst._chars);
    
    if(res != NULL){
        str_free(_chars);
        _chars = res;
    }
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::replace(const char* str, const char* dst)
{
    char* res = str_replace(_chars, str, dst);
    
    if(res != NULL){
        str_free(_chars);
        _chars = res;
    }
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::replaceAll(const utf8string_impl& str, const utf8string_impl& dst)
{
    char* res = str_replaceall(_chars, str._chars, dst._chars);
    
    if(res != NULL){
        str_free(_chars);
        _chars = res;
    }
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::replaceAll(const char* str, const char* dst)
{
    char* res = str_replaceall(_chars, str, dst);
    
    if(res != NULL){
        str_free(_chars);
        _chars = res;
    }
    
    return *this;
}

utf8string::utf8string_impl utf8string::utf8string_impl::left(size_t n) const
{
    char* str = str_left(_chars, n);
    
    return utf8string_impl(str);
}

utf8string::utf8string_impl utf8string::utf8string_impl::mid(size_t npos, size_t n) const
{
    char* str = str_mid(_chars, npos, n);
    
    return utf8string_impl(str);
}

utf8string::utf8string_impl utf8string::utf8string_impl::right(size_t n) const
{
    char* str = str_right(_chars, n);
    
    return utf8string_impl(str);
}

utf8string::utf8string_impl& utf8string::utf8string_impl::toUpper()
{
    str_toupper(_chars);
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::toLower()
{
    str_tolower(_chars);
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::remove(size_t npos, size_t n)
{
    char* res = str_remove(_chars, npos, n);
    
    if(res != NULL){
        str_free(_chars);
        _chars = res;
    }
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::remove(const utf8string_impl& src)
{
    char* res = str_remove(_chars, src._chars);
    
    if(res != NULL){
        str_free(_chars);
        _chars = res;
    }
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::remove(const char* src)
{
    char* res = str_remove(_chars, src);
    
    if(res != NULL){
        str_free(_chars);
        _chars = res;
    }
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::removeAll(const utf8string_impl& src)
{
    char* res = str_removeall(_chars, src._chars);
    
    if(res != NULL){
        str_free(_chars);
        _chars = res;
    }
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::removeAll(const char* src)
{
    char* res = str_removeall(_chars, src);
    
    if(res != NULL){
        str_free(_chars);
        _chars = res;
    }
    
    return *this;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::format(const char* fmt, ...)
{
    char buf[max_format_buffer_size];
    ::va_list vl;
    
    ::va_start(vl, fmt);
    int res = ::vsprintf(buf, fmt, vl);
    ::va_end(vl);
    if(res){
        str_free(_chars);
        _chars = str_alloc(static_cast<size_t>(res));
        str_copy(_chars, buf, res);
    }
    
    return *this;
}

int utf8string::utf8string_impl::toInt(bool* isOk) const
{
    return toInt(10, isOk);
}

int utf8string::utf8string_impl::toInt(int base, bool* isOk) const
{
    char* endPtr = NULL;
    int res = static_cast<int>(::strtol(_chars, &endPtr, base));
    if(isOk != NULL){
        *isOk = ((endPtr - _chars) != 0);
    }
    return res;
}

unsigned int utf8string::utf8string_impl::toUint(bool* isOk) const
{
    return toUint(10, isOk);
}

unsigned int utf8string::utf8string_impl::toUint(int base, bool* isOk) const
{
    char* endPtr = NULL;
    unsigned int res = static_cast<unsigned int>(::strtoul(_chars, &endPtr, base));
    if(isOk != NULL){
        *isOk = ((endPtr - _chars) != 0);
    }
    return res;
}

float utf8string::utf8string_impl::toFloat(bool* isOk) const
{
    char* endPtr = NULL;
    float res = static_cast<int>(::strtof(_chars, &endPtr));
    if(isOk != NULL){
        *isOk = ((endPtr - _chars) != 0);
    }
    return res;
}

double utf8string::utf8string_impl::toDouble(bool* isOk) const
{
    char* endPtr = NULL;
    double res = static_cast<int>(::strtod(_chars, &endPtr));
    if(isOk != NULL){
        *isOk = ((endPtr - _chars) != 0);
    }
    return res;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::setNum(int n)
{
    return format("%d",n);
}

utf8string::utf8string_impl& utf8string::utf8string_impl::setNum(unsigned int n)
{
    return format("%u",n);
}

utf8string::utf8string_impl& utf8string::utf8string_impl::setNum(float n)
{
    return format("%f",n);
}

utf8string::utf8string_impl& utf8string::utf8string_impl::setNum(double n)
{
    return format("%f",n);
}

utf8string::utf8string_impl utf8string::utf8string_impl::number(int n)
{
    utf8string_impl res;
    
    res.setNum(n);
    
    return res;
}

utf8string::utf8string_impl utf8string::utf8string_impl::number(unsigned int n)
{
    utf8string_impl res;
    
    res.setNum(n);
    
    return res;
}

utf8string::utf8string_impl utf8string::utf8string_impl::number(float n)
{
    utf8string_impl res;
    
    res.setNum(n);
    
    return res;
}

utf8string::utf8string_impl utf8string::utf8string_impl::number(double n)
{
    utf8string_impl res;
    
    res.setNum(n);
    
    return res;
}

utf8string::utf8string_impl& utf8string::utf8string_impl::operator=(const char* src)
{
    return set(src);
}

utf8string::utf8string_impl& utf8string::utf8string_impl::operator=(const utf8string_impl& src)
{
    return set(src);
}

bool utf8string::utf8string_impl::operator==(const char* src) const
{
    return equal(src);
}

bool utf8string::utf8string_impl::operator==(const utf8string_impl& src) const
{
    return equal(src);
}

bool utf8string::utf8string_impl::operator<(const char* src) const
{
    return less(src);
}

bool utf8string::utf8string_impl::operator<(const utf8string_impl& src) const
{
    return less(src);
}

utf8string::utf8string_impl& utf8string::utf8string_impl::operator+=(const char* src)
{
    return append(src);
}

utf8string::utf8string_impl& utf8string::utf8string_impl::operator+=(const utf8string_impl& src)
{
    return append(src);
}

utf8string::utf8string_impl utf8string::utf8string_impl::operator+(const char* src) const
{
    utf8string_impl res(*this);
    
    res.append(src);
    
    return res;
}

utf8string::utf8string_impl utf8string::utf8string_impl::operator+(const utf8string_impl& src) const
{
    utf8string_impl res(*this);
    
    res.append(src);
    
    return res;
}

unsigned int utf8string::utf8string_impl::operator[](int n) const
{
    return at(n);
}


