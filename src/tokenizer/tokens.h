#ifndef TOKENS_H
#define	TOKENS_H

#include "token.h"
#include <string>


class DelimitersToken
    :public Token
{
public:
    DelimitersToken(const std::string& content_, tokenid_t id_, tokenid_t gid_);
    DelimitersToken(const DelimitersToken& token_);
    ~DelimitersToken();
    
    DelimitersToken* clone() const;
    
    const std::string& content() const;
    void setContent(const std::string& content_);
    
    std::string toString() const;
    std::string value() const;
    
protected:
    std::string _content;
};

class WordToken
    :public Token
{
public:
    WordToken(const std::string& word_, tokenid_t id_, tokenid_t gid_);
    WordToken(const WordToken& token_);
    ~WordToken();
    
    WordToken* clone() const;
    
    const std::string& word() const;
    void setWord(const std::string& word_);
    
    std::string toString() const;
    std::string value() const;
    
protected:
    std::string _word;
};


class SequenceToken
    :public Token
{
public:
    SequenceToken(const std::string& begin_, const std::string& end_,
                  tokenid_t id_, tokenid_t gid_);
    SequenceToken(const std::string& begin_, const std::string& end_,
                  const std::string& content_, tokenid_t id_, tokenid_t gid_);
    SequenceToken(const std::string& begin_, const std::string& end_,
                  const std::string& content_, bool end_is_eof_,
                  tokenid_t id_, tokenid_t gid_);
    SequenceToken(const SequenceToken& token_);
    ~SequenceToken();
    
    SequenceToken* clone() const;
    
    std::string toString() const;
    std::string value() const;
    
    const std::string& begin() const;
    void setBegin(const std::string& begin_);
    
    const std::string& end() const;
    void setEnd(const std::string& end_);
    
    const std::string& content() const;
    void setContent(const std::string& content_);
    
    bool endIsEof() const;
    void setEndIsEof(bool end_is_eof_);
    
protected:
    std::string _begin;
    std::string _end;
    std::string _content;
    bool _end_is_eof;
};


class CNameToken
    :public Token
{
public:
    CNameToken(const std::string& name_, tokenid_t id_, tokenid_t gid_);
    CNameToken(const CNameToken& token_);
    ~CNameToken();
    
    CNameToken* clone() const;
    
    std::string toString() const;
    std::string value() const;
    
protected:
    tokenid_t _id;
    std::string _name;
};


class CNumberToken
    :public Token
{
public:
    CNumberToken(tokenid_t id_, tokenid_t gid_);
    CNumberToken(const std::string& str_value_, tokenid_t id_, tokenid_t gid_);
    CNumberToken(const CNumberToken& token_);
    ~CNumberToken();
    
    CNumberToken* clone() const;
    
    std::string toString() const;
    std::string value() const;
    
    bool fractional() const;
    
    int base() const;
    void setBase(int base_);
    
    char decPointChar() const;
    void setDecPointChar(char dec_point_char_);
    
    int toInt() const;
    unsigned int toUint() const;
    float toFloat() const;
    double toDouble() const;
    
protected:
    std::string _str_value;
    int _base;
    char _dec_point_char;
};

class CStringToken
    :public Token
{
public:
    CStringToken(const std::string& begin_, const std::string& end_,
                 tokenid_t id_, tokenid_t gid_);
    CStringToken(const std::string& begin_, const std::string& end_,
                 const std::string& content_, tokenid_t id_, tokenid_t gid_);
    CStringToken(const CStringToken& token_);
    ~CStringToken();
    
    CStringToken* clone() const;
    
    std::string toString() const;
    std::string value() const;
    
    const std::string& begin() const;
    void setBegin(const std::string& begin_);
    
    const std::string& end() const;
    void setEnd(const std::string& end_);
    
    const std::string& content() const;
    void setContent(const std::string& content_);
    
    static std::string escapeString(const std::string& str_);
    
protected:
    std::string _begin;
    std::string _end;
    std::string _content;
};


#endif	/* TOKENS_H */

