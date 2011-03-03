#ifndef _UTF8_STRING_H_
#define _UTF8_STRING_H_

#include <stddef.h>



class utf8string
{
public:
    utf8string();
    utf8string(utf8string& src);
    utf8string(const utf8string& src);
    utf8string(const char* src);
    ~utf8string();

    const char* c_str() const;

    size_t length() const;
    size_t size() const;

    unsigned int at(int n) const;

    bool equal(const utf8string& src) const;
    bool equal(const char* src) const;

    bool less(const utf8string& src) const;
    bool less(const char* src) const;

    bool empty() const;

    utf8string& clear();

    utf8string& set(utf8string& src);
    utf8string& set(const utf8string& src);
    utf8string& set(const char* src);

    utf8string& append(const utf8string& src);
    utf8string& append(const char* src);
    utf8string& prepend(const utf8string& src);
    utf8string& prepend(const char* src);
    utf8string& insert(const utf8string& src, size_t npos);
    utf8string& insert(const char* src, size_t npos);
    int indexOf(const utf8string& src) const;
    int indexOf(const char* src) const;
    int lastindexOf(const utf8string& src) const;
    int lastindexOf(const char* src) const;
    utf8string& replace(const utf8string& str, const utf8string& dst);
    utf8string& replace(const char* str, const char* dst);
    utf8string& replaceAll(const utf8string& str, const utf8string& dst);
    utf8string& replaceAll(const char* str, const char* dst);

    utf8string left(size_t n) const;
    utf8string mid(size_t npos, size_t n) const;
    utf8string right(size_t n) const;

    utf8string& toUpper();
    utf8string& toLower();

    utf8string& remove(size_t npos, size_t n);
    utf8string& remove(const utf8string& src);
    utf8string& remove(const char* src);
    utf8string& removeAll(const utf8string& src);
    utf8string& removeAll(const char* src);

    utf8string& format(const char* fmt, ...);

    int toInt(bool* isOk = NULL) const;
    int toInt(int base, bool* isOk = NULL) const;
    unsigned int toUint(bool* isOk = NULL) const;
    unsigned int toUint(int base, bool* isOk = NULL) const;
    float toFloat(bool* isOk = NULL) const;
    double toDouble(bool* isOk = NULL) const;

    utf8string& setNum(int n);
    utf8string& setNum(unsigned int n);
    utf8string& setNum(float n);
    utf8string& setNum(double n);

    static utf8string number(unsigned int n);
    static utf8string number(int n);
    static utf8string number(float n);
    static utf8string number(double n);

    utf8string& operator=(const char* src);
    utf8string& operator=(const utf8string& src);

    bool operator==(const char* src) const;
    bool operator==(const utf8string& src) const;

    bool operator!=(const char* src) const;
    bool operator!=(const utf8string& src) const;
    
    bool operator<(const char* src) const;
    bool operator<(const utf8string& src) const;

    utf8string& operator+=(const char* src);
    utf8string& operator+=(const utf8string& src);

    utf8string operator+(const char* src) const;
    utf8string operator+(const utf8string& src) const;

    unsigned int operator[](int n) const;


    class utf8char
    {
    public:
        static const size_t max_size = 4;

        static size_t size(const char* c);
        static size_t size(unsigned int c);
        static unsigned int decode(const char* c);
        static size_t encode(char* uc, unsigned int c);
    
        static bool validate(const char* c);
        
    private:
    };
private:
    class utf8string_rep;
    class utf8string_impl;

    utf8string(utf8string_impl& src);
    utf8string_rep* _modify_rep(utf8string_rep*& rep);

    utf8string_rep* _rep;
    
    class utf8string_rep
    {
    public:
        utf8string_rep();
        utf8string_rep(utf8string_rep* src);
        utf8string_rep(utf8string_impl* src);
        utf8string_rep(const utf8string_rep* src);
        utf8string_rep(const utf8string_impl* src);
        ~utf8string_rep();
    
        bool release();
    
        utf8string_impl* _data;
        int _links_count;
    };
    
    class utf8string_impl
    {
    public:
        static size_t length(const char* src);
        static size_t size(const char* src);
        static size_t size(const char* src, size_t n);
        static unsigned int at(const char* src, int n);
        static char* str_skip(char* src, size_t n);
        static const char* str_skip(const char* src, size_t n);
    
        static char* str_alloc(size_t s);
        static void str_free(char* & src);
        static char* str_copy(char* dst, const char* src);
        static char* str_copy(char* dst, const char* src, size_t s);
        static char* str_ncopy(char* dst, const char* src, size_t n);
        static char* str_copy(const char* src);
        static char* str_realloc(char*& src, size_t s, size_t src_d  = 0, size_t src_s = 0);
    
        static bool str_equal(const char* src, const char* dst);
        static bool str_empty(const char* src);
        static bool str_less(const char* src, const char* dst);

        static char* str_clear(char*& src);
    
        static char* str_append(const char* src, const char* dst);
        static char* str_prepend(const char* src, const char* dst);
        static char* str_insert(const char* src, const char* dst, size_t npos);
    
        static char* str_find(char* src, const char* dst);
        static const char* str_find(const char* src, const char* dst);
        static int str_indexof(const char* src, const char* dst);
        static int str_lastindexof(const char* src, const char* dst);
        static char* str_replace(const char* src, const char* str, const char* dst);
        static char* str_replaceall(const char* src, const char* str, const char* dst);
        static char* str_remove(const char* src, size_t npos, size_t n);
        static char* str_remove(const char* src, const char* dst);
        static char* str_removeall(const char* src, const char* dst);
    
        static char* str_left(const char* src, size_t n);
        static char* str_mid(const char* src, size_t npos, size_t n);
        static char* str_right(const char* src, size_t n);
        
        static char* str_toupper(char* src);
        static char* str_tolower(char* src);
    
        utf8string_impl();
        utf8string_impl(const utf8string_impl& src);
        utf8string_impl(const char* src);
        ~utf8string_impl();
        
        const char* c_str() const;
    
        size_t length() const;
        size_t size() const;
    
        unsigned int at(int n) const;
        
        bool equal(const utf8string_impl& src) const;
        bool equal(const char* src) const;
        
        bool less(const utf8string_impl& src) const;
        bool less(const char* src) const;

        bool empty() const;

        utf8string_impl& clear();
        
        utf8string_impl& set(const utf8string_impl& src);
        utf8string_impl& set(const char* src);
        
        utf8string_impl& append(const utf8string_impl& src);
        utf8string_impl& append(const char* src);
        utf8string_impl& prepend(const utf8string_impl& src);
        utf8string_impl& prepend(const char* src);
        utf8string_impl& insert(const utf8string_impl& src, size_t npos);
        utf8string_impl& insert(const char* src, size_t npos);
        int indexOf(const utf8string_impl& src) const;
        int indexOf(const char* src) const;
        int lastindexOf(const utf8string_impl& src) const;
        int lastindexOf(const char* src) const;
        utf8string_impl& replace(const utf8string_impl& str, const utf8string_impl& dst);
        utf8string_impl& replace(const char* str, const char* dst);
        utf8string_impl& replaceAll(const utf8string_impl& str, const utf8string_impl& dst);
        utf8string_impl& replaceAll(const char* str, const char* dst);
        
        utf8string_impl left(size_t n) const;
        utf8string_impl mid(size_t npos, size_t n) const;
        utf8string_impl right(size_t n) const;
        
        utf8string_impl& toUpper();
        utf8string_impl& toLower();
        
        utf8string_impl& remove(size_t npos, size_t n);
        utf8string_impl& remove(const utf8string_impl& src);
        utf8string_impl& remove(const char* src);
        utf8string_impl& removeAll(const utf8string_impl& src);
        utf8string_impl& removeAll(const char* src);
        
        static const size_t max_format_buffer_size = 256;
        
        utf8string_impl& format(const char* fmt, ...);
        
        int toInt(bool* isOk = NULL) const;
        int toInt(int base, bool* isOk = NULL) const;        
        unsigned int toUint(bool* isOk = NULL) const;
        unsigned int toUint(int base, bool* isOk = NULL) const;
        float toFloat(bool* isOk = NULL) const;
        double toDouble(bool* isOk = NULL) const;
        
        utf8string_impl& setNum(int n);
        utf8string_impl& setNum(unsigned int n);
        utf8string_impl& setNum(float n);
        utf8string_impl& setNum(double n);
        
        static utf8string_impl number(int n);
        static utf8string_impl number(unsigned int n);
        static utf8string_impl number(float n);
        static utf8string_impl number(double n);
        
        utf8string_impl& operator=(const char* src);
        utf8string_impl& operator=(const utf8string_impl& src);

        bool operator==(const char* src) const;
        bool operator==(const utf8string_impl& src) const;
        
        bool operator<(const char* src) const;
        bool operator<(const utf8string_impl& src) const;

        utf8string_impl& operator+=(const char* src);
        utf8string_impl& operator+=(const utf8string_impl& src);

        utf8string_impl operator+(const char* src) const;
        utf8string_impl operator+(const utf8string_impl& src) const;
        
        unsigned int operator[](int n) const;
        
    private:
        char* _chars;
    };
};

#endif//_UTF8_STRING_H_
