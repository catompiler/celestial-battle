#include "tokens.h"
#include <locale>
#include <stdlib.h>
#include <algorithm>


//DelimitersToken

DelimitersToken::DelimitersToken(const std::string& content_, tokenid_t id_, tokenid_t gid_)
    :Token(id_, gid_)
{
    _content = content_;
}

DelimitersToken::DelimitersToken(const DelimitersToken& token_)
    :Token(token_)
{
    _content = token_._content;
}

DelimitersToken::~DelimitersToken()
{
}

DelimitersToken* DelimitersToken::clone() const
{
    return new DelimitersToken(*this);
}

const std::string& DelimitersToken::content() const
{
    return _content;
}

void DelimitersToken::setContent(const std::string& content_)
{
    _content = content_;
}

std::string DelimitersToken::toString() const
{
    return _content;
}

std::string DelimitersToken::value() const
{
    return _content;
}


//WordToken

WordToken::WordToken(const std::string& word_, tokenid_t id_, tokenid_t gid_)
    :Token(id_, gid_)
{
    _word = word_;
}

WordToken::WordToken(const WordToken& token_)
    :Token(token_)
{
    _word = token_._word;
}

WordToken::~WordToken()
{
}

WordToken* WordToken::clone() const
{
    return new WordToken(*this);
}

const std::string& WordToken::word() const
{
    return _word;
}

void WordToken::setWord(const std::string& word_)
{
    _word = word_;
}

std::string WordToken::toString() const
{
    return _word;
}

std::string WordToken::value() const
{
    return _word;
}


//SequenceToken

SequenceToken::SequenceToken(const std::string& begin_, const std::string& end_,
                             tokenid_t id_, tokenid_t gid_)
    :Token(id_, gid_)
{
    _begin = begin_;
    _end = end_;
    _content = std::string();
    _end_is_eof = false;
}

SequenceToken::SequenceToken(const std::string& begin_, const std::string& end_,
                             const std::string& content_, tokenid_t id_, tokenid_t gid_)
    :Token(id_, gid_)
{
    _begin = begin_;
    _end = end_;
    _content = content_;
    _end_is_eof = false;
}

SequenceToken::SequenceToken(const std::string& begin_, const std::string& end_,
                             const std::string& content_, bool end_is_eof_,
                             tokenid_t id_, tokenid_t gid_)
    :Token(id_, gid_)
{
    _begin = begin_;
    _end = end_;
    _content = content_;
    _end_is_eof = end_is_eof_;
}

SequenceToken::SequenceToken(const SequenceToken& token_)
    :Token(token_)
{
    _begin = token_._begin;
    _end = token_._end;
    _content = token_._content;
    _end_is_eof = token_._end_is_eof;
}

SequenceToken::~SequenceToken()
{
}

SequenceToken* SequenceToken::clone() const
{
    return new SequenceToken(*this);
}

std::string SequenceToken::toString() const
{
    std::string res = _begin + _content;
    if(!_end_is_eof) res += _end;
    return res;
}

std::string SequenceToken::value() const
{
    return _content;
}

const std::string& SequenceToken::begin() const
{
    return _begin;
}

void SequenceToken::setBegin(const std::string& begin_)
{
    _begin = begin_;
}

const std::string& SequenceToken::end() const
{
    return _end;
}

void SequenceToken::setEnd(const std::string& end_)
{
    _end = end_;
}

const std::string& SequenceToken::content() const
{
    return _content;
}

void SequenceToken::setContent(const std::string& content_)
{
    _content = content_;
}

bool SequenceToken::endIsEof() const
{
    return _end_is_eof;
}

void SequenceToken::setEndIsEof(bool end_is_eof_)
{
    _end_is_eof = end_is_eof_;
}


//NameToken

CNameToken::CNameToken(const std::string& name_, tokenid_t id_, tokenid_t gid_)
    :Token(id_, gid_)
{
    _name = name_;
}

CNameToken::CNameToken(const CNameToken& token_)
    :Token(token_)
{
    _name = token_._name;
}

CNameToken::~CNameToken()
{
}

CNameToken* CNameToken::clone() const
{
    return new CNameToken(*this);
}

std::string CNameToken::toString() const
{
    return _name;
}

std::string CNameToken::value() const
{
    return _name;
}


//CNumberToken

CNumberToken::CNumberToken(tokenid_t id_, tokenid_t gid_)
    :Token(id_, gid_)
{
    _base = 10;
    _dec_point_char = std::use_facet<std::numpunct<char> >(std::locale()).decimal_point();
}

CNumberToken::CNumberToken(const std::string& str_value_, tokenid_t id_, tokenid_t gid_)
    :Token(id_, gid_)
{
    _str_value = str_value_;
    _base = 10;
    _dec_point_char = std::use_facet<std::numpunct<char> >(std::locale()).decimal_point();
}

CNumberToken::CNumberToken(const CNumberToken& token_)
    :Token(token_)
{
    _str_value = token_._str_value;
    _base = token_._base;
    _dec_point_char = token_._dec_point_char;
}

CNumberToken::~CNumberToken()
{
}

CNumberToken* CNumberToken::clone() const
{
    return new CNumberToken(*this);
}

std::string CNumberToken::toString() const
{
    return _str_value;
}

std::string CNumberToken::value() const
{
    return _str_value;
}

bool CNumberToken::fractional() const
{
    std::string fract_symbols = std::string(1, _dec_point_char);
    if(_base == 10) fract_symbols += std::string("eE");
    return std::find_first_of(_str_value.begin(), _str_value.end(),
                    fract_symbols.begin(), fract_symbols.end()) != _str_value.end();
}

int CNumberToken::base() const
{
    return _base;
}

void CNumberToken::setBase(int base_)
{
    _base = base_;
}

char CNumberToken::decPointChar() const
{
    return _dec_point_char;
}

void CNumberToken::setDecPointChar(char dec_point_char_)
{
    _dec_point_char = dec_point_char_;
}

int CNumberToken::toInt() const
{
    return static_cast<int>(strtol(_str_value.c_str(), NULL, _base));
}

unsigned int CNumberToken::toUint() const
{
    return static_cast<unsigned int>(strtoul(_str_value.c_str(), NULL, _base));
}

float CNumberToken::toFloat() const
{
    if(_dec_point_char != '.'){
        std::string s(_str_value);
        std::replace(s.begin(), s.end(), _dec_point_char, '.');
        return static_cast<float>(strtol(s.c_str(), NULL, _base));
    }
    return static_cast<float>(strtof(_str_value.c_str(), NULL));
}

double CNumberToken::toDouble() const
{
    if(_dec_point_char != '.'){
        std::string s(_str_value);
        std::replace(s.begin(), s.end(), _dec_point_char, '.');
        return strtol(s.c_str(), NULL, _base);
    }
    return strtod(_str_value.c_str(), NULL);
}



//CStringToken

CStringToken::CStringToken(const std::string& begin_, const std::string& end_,
                           tokenid_t id_, tokenid_t gid_)
    :Token(id_, gid_)
{
    _begin = begin_;
    _end = end_;
    _content = std::string();
}

CStringToken::CStringToken(const std::string& begin_, const std::string& end_,
                           const std::string& content_, tokenid_t id_, tokenid_t gid_)
    :Token(id_, gid_)
{
    _begin = begin_;
    _end = end_;
    _content = content_;
}

CStringToken::CStringToken(const CStringToken& token_)
    :Token(token_)
{
    _begin = token_._begin;
    _end = token_._end;
    _content = token_._content;
}

CStringToken::~CStringToken()
{
}

CStringToken* CStringToken::clone() const
{
    return new CStringToken(*this);
}

std::string CStringToken::toString() const
{
    return _begin + escapeString(_content) + _end;
}

std::string CStringToken::escapeString(const std::string& str_)
{
    std::string res;
    //'\'','\"','?','\\','\0','\a','\b','\f','\n','\r','\t','\v'
    for(std::string::const_iterator it = str_.begin(); it != str_.end(); ++ it){
        switch(*it){
            case '\'':
                res += "\\\'";
                break;
            case '\"':
                res += "\\\"";
                break;
            case '\\':
                res += "\\\\";
                break;
            case '\0':
                res += "\\0";
                break;
            case '\a':
                res += "\\a";
                break;
            case '\b':
                res += "\\b";
                break;
            case '\f':
                res += "\\f";
                break;
            case '\n':
                res += "\\n";
                break;
            case '\r':
                res += "\\r";
                break;
            case '\t':
                res += "\\t";
                break;
            case '\v':
                res += "\\v";
                break;
            default:
                res += *it;
                break;
        }
    }
    return res;
}

std::string CStringToken::value() const
{
    return _content;
}

const std::string& CStringToken::begin() const
{
    return _begin;
}

void CStringToken::setBegin(const std::string& begin_)
{
    _begin = begin_;
}

const std::string& CStringToken::end() const
{
    return _end;
}

void CStringToken::setEnd(const std::string& end_)
{
    _end = end_;
}

const std::string& CStringToken::content() const
{
    return _content;
}

void CStringToken::setContent(const std::string& content_)
{
    _content = content_;
}
