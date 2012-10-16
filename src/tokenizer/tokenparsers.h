#ifndef TOKENPARSERS_H
#define	TOKENPARSERS_H

#include "tokenparser.h"
#include "tokens.h"
#include "tokenizer.h"
#include <stddef.h>
#include <string>
#include <map>



class DelimitersTokenParser
    :public TokenParser
{
public:
    DelimitersTokenParser(const std::string& delim_, tokenid_t id_, tokenid_t gid_);
    DelimitersTokenParser(const DelimitersTokenParser& parser_);
    ~DelimitersTokenParser();
    
    const std::string& delimiters() const;
    void setDelimiters(const std::string& delim_);
    
    DelimitersToken* parse(Tokenizer* tokenizer_) const;
    
protected:
    std::string _delim;
};


class WordTokenParser
    :public TokenParser
{
public:
    WordTokenParser(const std::string& word_, tokenid_t id_, tokenid_t gid_);
    WordTokenParser(const WordTokenParser& parser_);
    ~WordTokenParser();
    
    const std::string& word() const;
    void setWord(const std::string& word_);
    
    WordToken* parse(Tokenizer* tokenizer_) const;
    
protected:
    std::string _word;
};


class SequenceTokenParser
    :public TokenParser
{
public:
    SequenceTokenParser(const std::string& begin_, const std::string& end_,
                        tokenid_t id_, tokenid_t gid_);
    SequenceTokenParser(const std::string& begin_, const std::string& end_,
                        bool eof_is_valid_end_, tokenid_t id_, tokenid_t gid_);
    SequenceTokenParser(const SequenceTokenParser& token_);
    ~SequenceTokenParser();
    
    const std::string& begin() const;
    void setBegin(const std::string& begin_);
    
    const std::string& end() const;
    void setEnd(const std::string& end_);
    
    bool eofIsValidEnd() const;
    void setEofIsValidEnd(bool valid_);
    
    SequenceToken* parse(Tokenizer* tokenizer_) const;
    
protected:
    std::string _begin;
    std::string _end;
    bool _eof_is_valid_end;
};

//[a-zA-Z_]+[a-zA-Z_0-9]*
class CNameTokenParser
    :public TokenParser
{
public:
    CNameTokenParser(tokenid_t id_, tokenid_t gid_);
    CNameTokenParser(const CNameTokenParser& parser_);
    ~CNameTokenParser();
    
    CNameToken* parse(Tokenizer* tokenizer_) const;
};


class CNumberTokenParser
    :public TokenParser
{
public:
    
    enum dec_point_type{DOT=0, COMMA=1};
    
    CNumberTokenParser(tokenid_t id_, tokenid_t gid_);
    CNumberTokenParser(dec_point_type type_, tokenid_t id_, tokenid_t gid_);
    CNumberTokenParser(const CNumberTokenParser& parser_);
    ~CNumberTokenParser();
    
    CNumberToken* parse(Tokenizer* tokenizer_) const;
    
    dec_point_type decPointType() const;
    void setDecPointType(dec_point_type type_);
    
    std::string getDecPointStr() const;
    char getDecPointChar() const;
    
    static std::string getDecPointStr(dec_point_type type_);
    static char getDecPointChar(dec_point_type type_);
    
    static dec_point_type decPointType(char dp_);
    static dec_point_type decPointType(const std::string& dp_);

    static bool is_oct_digit(char digit_);
    static bool is_dec_digit(char digit_);
    static bool is_hex_digit(char digit_);
    
    static bool is_digit_of_base(char digit_, unsigned int base_);
    
protected:
    dec_point_type _dec_point_type;
};



class CStringTokenParser
    :public TokenParser
{
public:
    CStringTokenParser(const std::string& begin_, const std::string& end_,
                       tokenid_t id_, tokenid_t gid_);
    CStringTokenParser(const CStringTokenParser& tokenparser_);
    ~CStringTokenParser();
    
    CStringToken* parse(Tokenizer* tokenizer_) const;
        
    const std::string& begin() const;
    void setBegin(const std::string& begin_);
    
    const std::string& end() const;
    void setEnd(const std::string& end_);
    
protected:
    std::string _begin;
    std::string _end;
    
    static const size_t _arr_esc_size = 8;
    static const char _from_esc[_arr_esc_size];
    static const char _to_esc[_arr_esc_size];
};



#endif	/* TOKENPARSERS_H */

