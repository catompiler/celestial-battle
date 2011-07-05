#include "windows_iconv.h"
#include <stddef.h>
#include <string.h>
#include <vector>
#include <windows.h>
#include <iostream>


std::string Iconv::fromLocal(const std::string& str_)
{
    std::string res;
    std::vector<wchar_t> vec_ustr;
    std::vector<char> vec_utf8str;
    size_t size_s = str_.length();
    
    int len = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS,
                str_.c_str(), size_s, NULL, 0);
    
    if(len > 0){
        size_t size_us = len;
        vec_ustr.resize(size_us + 1);
        MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS,
                str_.c_str(), size_s, &vec_ustr[0], size_us);
        
        int l = WideCharToMultiByte(CP_UTF8, 0,
                &vec_ustr[0], size_us,
                NULL, 0, NULL, NULL);
        if(l > 0){
            size_t size_utf8s = l;
            vec_utf8str.resize(size_utf8s + 1);
            WideCharToMultiByte(CP_UTF8, 0,
                &vec_ustr[0], size_us,
                &vec_utf8str[0], size_utf8s, NULL, NULL);
            res = std::string(&vec_utf8str[0]);
        }
    }
    return res;
}

std::string Iconv::toLocal(const std::string& str_)
{
    std::string res;
    std::vector<wchar_t> vec_ustr;
    std::vector<char> vec_str;
    size_t size_utf8s = str_.length();
    
    int len = MultiByteToWideChar(CP_UTF8, 0,
                str_.c_str(), size_utf8s, NULL, 0);
    
    if(len > 0){
        size_t size_us = len;
        vec_ustr.resize(size_us + 1);
        MultiByteToWideChar(CP_UTF8, 0,
                str_.c_str(), size_utf8s, &vec_ustr[0], size_us);
        
        int l = WideCharToMultiByte(CP_ACP, 0,
                &vec_ustr[0], size_us, NULL, 0, NULL, NULL);
        if(l > 0){
            size_t size_s = l;
            vec_str.resize(size_s + 1);
            WideCharToMultiByte(CP_ACP, 0,
                    &vec_ustr[0], size_us,
                    &vec_str[0], size_s, NULL, NULL);
            //std::cout << "GetLastError() = " << GetLastError() << std::endl;
            res = std::string(&vec_str[0]);
        }
    }
    return res;
}
