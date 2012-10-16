#include "tokenparsers.h"
#include "tokenizer.h"
#include "parseexception.h"
#include <locale>
#include <iostream>
#include <algorithm>
#include <sstream>



//DelimitersTokenParser

DelimitersTokenParser::DelimitersTokenParser(const std::string& delim_, tokenid_t id_, tokenid_t gid_)
    :TokenParser(id_, gid_)
{
    _delim = delim_;
}

DelimitersTokenParser::DelimitersTokenParser(const DelimitersTokenParser& parser_)
    :TokenParser(parser_)
{
    _delim = parser_._delim;
}

DelimitersTokenParser::~DelimitersTokenParser()
{
}

const std::string& DelimitersTokenParser::delimiters() const
{
    return _delim;
}

void DelimitersTokenParser::setDelimiters(const std::string& delim_)
{
    _delim = delim_;
}

DelimitersToken* DelimitersTokenParser::parse(Tokenizer* tokenizer_) const
{
    if(tokenizer_->atEnd()) return NULL;
    
    if(_delim.find(tokenizer_->peek()) == std::string::npos) return NULL;
    
    std::string res;
    
    while(_delim.find(tokenizer_->peek()) != std::string::npos &&
            !tokenizer_->atEnd()){
        res += tokenizer_->get();
    }
    
    return res.empty() ? NULL : new DelimitersToken(res, _id, _gid);
}


//WordTokenParser

WordTokenParser::WordTokenParser(const std::string& word_, tokenid_t id_, tokenid_t gid_)
    :TokenParser(id_, gid_)
{
    _word = word_;
}

WordTokenParser::WordTokenParser(const WordTokenParser& parser_)
    :TokenParser(parser_)
{
    _word = parser_._word;
}

WordTokenParser::~WordTokenParser()
{
}

const std::string& WordTokenParser::word() const
{
    return _word;
}

void WordTokenParser::setWord(const std::string& word_)
{
    _word = word_;
}

WordToken* WordTokenParser::parse(Tokenizer* tokenizer_) const
{
    size_t l = _word.size();
    if(tokenizer_->remaining() < l) return NULL;
    if(_word != tokenizer_->peek(l)) return NULL;
    tokenizer_->skip(l);
    return new WordToken(_word, _id, _gid);
}


//SequenceTokenParser

SequenceTokenParser::SequenceTokenParser(const std::string& begin_, const std::string& end_,
                                         tokenid_t id_, tokenid_t gid_)
    :TokenParser(id_, gid_)
{
    _begin = begin_;
    _end = end_;
    _eof_is_valid_end = false;
}

SequenceTokenParser::SequenceTokenParser(const std::string& begin_, const std::string& end_,
                                        bool eof_is_valid_end_, tokenid_t id_, tokenid_t gid_)
    :TokenParser(id_, gid_)
{
    _begin = begin_;
    _end = end_;
    _eof_is_valid_end = eof_is_valid_end_;
}

SequenceTokenParser::SequenceTokenParser(const SequenceTokenParser& parser_)
    :TokenParser(parser_)
{
    _begin = parser_._begin;
    _end = parser_._end;
    _eof_is_valid_end = parser_._eof_is_valid_end;
}

SequenceTokenParser::~SequenceTokenParser()
{
}

const std::string& SequenceTokenParser::begin() const
{
    return _begin;
}

void SequenceTokenParser::setBegin(const std::string& begin_)
{
    _begin = begin_;
}

const std::string& SequenceTokenParser::end() const
{
    return _end;
}

void SequenceTokenParser::setEnd(const std::string& end_)
{
    _end = end_;
}

bool SequenceTokenParser::eofIsValidEnd() const
{
    return _eof_is_valid_end;
}

void SequenceTokenParser::setEofIsValidEnd(bool valid_)
{
    _eof_is_valid_end = valid_;
}

SequenceToken* SequenceTokenParser::parse(Tokenizer* tokenizer_) const
{
    size_t beg_len = _begin.length();
    if(tokenizer_->remaining() < _begin.length()){
        return NULL;
    }
    
    if(tokenizer_->peek(beg_len) != _begin){
        return NULL;
    }
    
    tokenizer_->pushPos();
    
    tokenizer_->skip(beg_len);
    
    size_t end_len = _end.length();
    bool end_is_eof = false;
    std::string token_str;
    
    for(;;){
        if(!_eof_is_valid_end){
            if(/*tokenizer_->atEnd() || */tokenizer_->remaining() < end_len){
                //tokenizer_->popPos();
                throw(NoSquenceEndParseException(tokenizer_->getAndPopPos()));
            }
        }else{
            if(tokenizer_->atEnd()){
                end_is_eof = true;
                break;
            }
        }
        if(tokenizer_->peek(end_len) == _end){
            tokenizer_->skip(end_len);
            break;
        }
        token_str += tokenizer_->get();
    }
    tokenizer_->forgetPos();
    
    SequenceToken* res_token = new SequenceToken(_begin, _end, token_str, end_is_eof, _id, _gid);
    //res_token->setEndIsEof(end_is_eof);
    
    return res_token;
}


//NameTokenParser

CNameTokenParser::CNameTokenParser(tokenid_t id_, tokenid_t gid_)
    :TokenParser(id_, gid_)
{
}

CNameTokenParser::CNameTokenParser(const CNameTokenParser& parser_)
    :TokenParser(parser_)
{
}

CNameTokenParser::~CNameTokenParser()
{
}

CNameToken* CNameTokenParser::parse(Tokenizer* tokenizer_) const
{
    static const std::string underline = "_";
    
    if(tokenizer_->atEnd()) return NULL;
    
    std::string c = tokenizer_->peek();
    
    if(c != underline && !isalpha(*c.begin())) return NULL;
    
    std::string res = tokenizer_->get();
    
    for(;!tokenizer_->atEnd();){
        c = tokenizer_->peek();
        if(c != underline && !isalnum(*c.begin())){
            break;
        }
        res += tokenizer_->get();
    }
    
    return new CNameToken(res, _id, _gid);
}


//CNumberTokenParser

CNumberTokenParser::CNumberTokenParser(tokenid_t id_, tokenid_t gid_)
    :TokenParser(id_, gid_)
{
    _dec_point_type = decPointType(
                std::use_facet<std::numpunct<char> >(std::locale()).decimal_point()
            );
}

CNumberTokenParser::CNumberTokenParser(dec_point_type type_,
                                       tokenid_t id_, tokenid_t gid_)
    :TokenParser(id_, gid_)
{
    _dec_point_type = type_;
}


CNumberTokenParser::CNumberTokenParser(const CNumberTokenParser& parser_)
    :TokenParser(parser_)
{
    _dec_point_type = parser_._dec_point_type;
}

CNumberTokenParser::~CNumberTokenParser()
{
}

CNumberToken* CNumberTokenParser::parse(Tokenizer* tokenizer_) const
{
    if(tokenizer_->atEnd()) return NULL;
    
    std::locale loc;
    
    //const std::string dp_str = getDotStr();
    const char dp_char = getDecPointChar();
    const std::string e_str = "eE";
    const std::string x_str = "xX";
    //const char e_char = 'e';
    const std::string sign_str = "-+";
    
    /*enum read_flags_t{NONE_READED = 0, BASE_READED = 1, DOT_READED = 2,
                       MANTISSA_READED = 4, FRACT_READED = 8, E_READED = 16,
                       E_SIGN_READED = 32, EXPONENT_READED = 64,
                       NUMBER_READED = 128};*/
    //
    enum read_state_t{READING_MANTISS, READED_DP, READING_FRACT, READED_E, READED_E_SIGN, READING_EXP};
    //
    //unsigned int read_flags = NONE_READED;
    read_state_t read_state = READING_MANTISS;
    
    //const size_t base_max = 16;
    size_t base = 10;//default value
    
    std::string s = tokenizer_->peek();
    char c = 0x0;
    std::string number_str;
    
    tokenizer_->pushPos();
    
    // "N*" || ".N" where N is a valid number char
    if(!std::isdigit(*s.begin(), loc)){//may be "."
        if(*s.begin() != dp_char){//not a nuber
            tokenizer_->popPos();
            return NULL;
        }
        if(tokenizer_->remaining() < 2){
            tokenizer_->popPos();
            return NULL;
        }
        s = tokenizer_->peek(2);
        if(!std::isdigit(*(s.begin() + 1), loc)){
            tokenizer_->popPos();
            return NULL;
        }
    }
    
    //if the number starts with 0
    if(*s.begin() == '0'){
        if(tokenizer_->remaining() >= 2){
            //get a second character
            if(s.length() == 1){
                s = tokenizer_->peek(2);
            }
            c = *(s.begin() + 1);

            //if it is equal to 'x' (0x) -> may be base = 16
            if(x_str.find(c) != std::string::npos){
                //if third character
                if(tokenizer_->remaining() >= 3){
                    s = tokenizer_->peek(3);
                    c = *(s.begin() + 2);
                    //is digit
                    if(is_hex_digit(c)){
                        base = 16;
                    }
                }
            }//if the digit -> base = 8
            else{
                if(is_oct_digit(c)){
                    base = 8;
                }else if(is_dec_digit(c)){
                    //tokenizer_->popPos();
                    throw(InvalitOctDigitParseException(tokenizer_->getAndPopPos()));
                }
            }
        }
    }
    
    bool break_loop = false;
    //read number
    for(;tokenizer_->remaining();){
        
        c = *tokenizer_->peek().begin();

        //if character not in a number's(base) alphabet
        if(!is_digit_of_base(c, base)){
            //if it is a decimal point
            if(c == dp_char){
                switch(read_state){
                    case READING_MANTISS:
                        read_state = READED_DP;
                        break;
                    case READED_DP:
                    case READING_FRACT:
                        //tokenizer_->popPos();
                        throw(TooManyDecPointsParseException(tokenizer_->getAndPopPos()));
                        break;
                    case READED_E:
                    case READED_E_SIGN:
                        //tokenizer_->popPos();
                        throw(NoDigitsInExpParseException(tokenizer_->getAndPopPos()));
                        break;
                    case READING_EXP:
                        break_loop = true;
                        break;
                }
            }else if(e_str.find(c) != std::string::npos){
                if(base != 10){
                    break_loop = true;
                }else{
                    switch(read_state){
                        case READING_MANTISS:
                        case READING_FRACT:
                        case READED_DP:
                            read_state = READED_E;
                            break;
                        case READED_E:
                        case READED_E_SIGN:
                            //tokenizer_->popPos();
                            throw(NoDigitsInExpParseException(tokenizer_->getAndPopPos()));
                            break;
                        case READING_EXP:
                            break_loop = true;
                            break;
                    }
                }
            }else if(x_str.find(c) != std::string::npos){
                switch(read_state){
                    case READING_MANTISS:
                        if(base != 16 || number_str.length() > 1){
                            break_loop = true;
                        }
                        break;
                    case READED_E:
                    case READED_E_SIGN:
                        //tokenizer_->popPos();
                        throw(NoDigitsInExpParseException(tokenizer_->getAndPopPos()));
                        break;
                    case READED_DP:
                    case READING_FRACT:
                    case READING_EXP:
                        break_loop = true;
                        break;
                }
            }else if(sign_str.find(c) != std::string::npos){
                switch(read_state){
                    case READED_E:
                        read_state = READED_E_SIGN;
                        break;
                    case READED_E_SIGN:
                        //tokenizer_->popPos();
                        throw(NoDigitsInExpParseException(tokenizer_->getAndPopPos()));
                        break;
                    case READING_MANTISS:
                    case READED_DP:
                    case READING_FRACT:
                    case READING_EXP:
                        break_loop = true;
                        break;
                }
            }
            else{
                switch(read_state){
                    case READED_E:
                    case READED_E_SIGN:
                        //tokenizer_->popPos();
                        throw(NoDigitsInExpParseException(tokenizer_->getAndPopPos()));
                        break;
                    case READING_MANTISS:
                    case READED_DP:
                    case READING_FRACT:
                    case READING_EXP:
                        break_loop = true;
                        break;
                }
            }
        }else{
            switch(read_state){
                case READED_DP:
                    read_state = READING_FRACT;
                    break;
                case READED_E:
                    read_state = READING_EXP;
                    break;
                case READED_E_SIGN:
                    read_state = READING_EXP;
                    break;
                case READING_MANTISS:
                case READING_FRACT:
                case READING_EXP:
                    break;
            }
        }
        
        if(break_loop) break;
        //...
        number_str += tokenizer_->get();
        
        if(tokenizer_->remaining() == 0){
            switch(read_state){
                case READED_E:
                case READED_E_SIGN:
                    //tokenizer_->popPos();
                    throw(NoDigitsInExpParseException(tokenizer_->getAndPopPos()));
                    break;
                case READING_MANTISS:
                case READED_DP:
                case READING_FRACT:
                case READING_EXP:
                    break_loop = true;
                    break;
            }
        }
    }
    
    /*std::cout << "Number token: \"" << number_str << "\" " <<
                 "base = " << base << std::endl;*/
    
    tokenizer_->forgetPos();
    
    CNumberToken* res = new CNumberToken(number_str, _id, _gid);
    res->setBase(static_cast<int>(base));
    res->setDecPointChar(dp_char);
    
    return res;
}

/*
switch(read_state){
                    case READING_MANTISS:
                        break;
                    case READED_DOT:
                        break;
                    case READING_FRACT:
                        break;
                    case READED_E:
                        break;
                    case READED_E_SIGN:
                        break;
                    case READING_EXP:
                        break;
                    default:
                        break;
                }
*/

CNumberTokenParser::dec_point_type CNumberTokenParser::decPointType() const
{
    return _dec_point_type;
}

void CNumberTokenParser::setDecPointType(dec_point_type type_)
{
    _dec_point_type = type_;
}

std::string CNumberTokenParser::getDecPointStr() const
{
    return getDecPointStr(_dec_point_type);
}

char CNumberTokenParser::getDecPointChar() const
{
    return getDecPointChar(_dec_point_type);
}

std::string CNumberTokenParser::getDecPointStr(dec_point_type type_)
{
    return type_ == DOT ? "." : ",";
}

char CNumberTokenParser::getDecPointChar(dec_point_type type_)
{
    return type_ == DOT ? '.' : ',';
}

CNumberTokenParser::dec_point_type CNumberTokenParser::decPointType(char dp_)
{
    return dp_ == ',' ? COMMA : DOT;
}

CNumberTokenParser::dec_point_type CNumberTokenParser::decPointType(const std::string& dp_)
{
    return dp_ == "," ? COMMA : DOT;
}

bool CNumberTokenParser::is_oct_digit(char digit_)
{
    return digit_ >= '0' && digit_ <= '7';
}

bool CNumberTokenParser::is_dec_digit(char digit_)
{
    return digit_ >= '0' && digit_ <= '9';
}

bool CNumberTokenParser::is_hex_digit(char digit_)
{
    return (digit_ >= '0' && digit_ <= '9') ||
           (digit_ >= 'a' && digit_ <= 'f') ||
           (digit_ >= 'A' && digit_ <= 'F');
}

bool CNumberTokenParser::is_digit_of_base(char digit_, unsigned int base_)
{
    static const std::string number_alphabet_str_lo = "0123456789abcdef";
    static const std::string number_alphabet_str_hi = "0123456789ABCDEF";
    const unsigned int base_max = 16;
    
    if(base_ > base_max) return false;
    
    switch(base_){
        case 8:
            return is_oct_digit(digit_);
        case 16:
            return is_hex_digit(digit_);
        case 10:
            return is_dec_digit(digit_);
        default:
            break;
    }
    
    return std::binary_search(number_alphabet_str_lo.begin(),
                              number_alphabet_str_lo.begin() + base_, digit_) ||
           std::binary_search(number_alphabet_str_hi.begin(),
                              number_alphabet_str_hi.begin() + base_, digit_);
}


//CStringTokenParser

//const size_t CStringTokenParser::_arr_esc_size;
const char CStringTokenParser::_from_esc[_arr_esc_size] = {/*'\'','\"','?','\\',*/'0','a','b','f','n','r','t','v'};
const char CStringTokenParser::_to_esc[_arr_esc_size] = {/*'\'','\"','?','\\',*/'\0','\a','\b','\f','\n','\r','\t','\v'};

CStringTokenParser::CStringTokenParser(const std::string& begin_, const std::string& end_,
                                       tokenid_t id_, tokenid_t gid_)
    :TokenParser(id_, gid_)
{
    _begin = begin_;
    _end = end_;
}

CStringTokenParser::CStringTokenParser(const CStringTokenParser& tokenparser_)
    :TokenParser(tokenparser_)
{
    _begin = tokenparser_._begin;
    _end = tokenparser_._end;
}

CStringTokenParser::~CStringTokenParser()
{
}
/*
 * http://ru.cppreference.com/w/cpp/language/escape
 */
CStringToken* CStringTokenParser::parse(Tokenizer* tokenizer_) const
{
    size_t beg_len = _begin.length();
    if(tokenizer_->remaining() < _begin.length()){
        return NULL;
    }
    
    if(tokenizer_->peek(beg_len) != _begin){
        return NULL;
    }
    
    tokenizer_->pushPos();
    tokenizer_->skip(beg_len);
    
    size_t end_len = _end.length();
    
    std::string token_str;
    
    std::string s;
    char c = 0;
    
    const char esc_char = '\\';
    const char newline_char = '\n';
    
    bool cur_esc = false;
    
    for(;;){
        if(/*tokenizer_->atEnd() || */tokenizer_->remaining() < end_len){
            //tokenizer_->popPos();
            throw(NoStringEndParseException(tokenizer_->getAndPopPos()));
        }
        
        s = tokenizer_->peek();
        c = *s.begin();
        
        if(!cur_esc){
        
            //c = std::tolower(*s.begin(), loc);
            if(c == esc_char){
                tokenizer_->skip();
                cur_esc = true;
                continue;
            }
            
            if(c == newline_char){
                //tokenizer_->popPos();
                throw(NoStringEndParseException(tokenizer_->getAndPopPos()));
            }

            if(*s.begin() == *_end.begin() &&
                        tokenizer_->peek(end_len) == _end){
                tokenizer_->skip(end_len);
                break;
            }
            token_str += tokenizer_->get();
        }else{
            c = *s.begin();
            
            //1) is oct
            //2) is hex
            //3) is \n
            //4) is esc
            //5) default
            
            if(CNumberTokenParser::is_oct_digit(c)){//oct
                std::string char_code_str;
                for(int i = 0; !tokenizer_->atEnd() && i < 3; i ++){
                    c = *tokenizer_->peek().begin();
                    if(CNumberTokenParser::is_oct_digit(c)){
                        char_code_str += tokenizer_->get();
                    }else{
                        break;
                    }
                }
                std::stringstream ss(char_code_str);
                ss.setf(std::ios::oct, std::ios::basefield);
                int c_i;
                ss >> c_i;

                token_str += static_cast<char>(c_i);
                
            }else if(c == 'x'){//hex
                
                tokenizer_->skip();
                if(tokenizer_->atEnd()){
                    //tokenizer_->popPos();
                    throw(NoStringEndParseException(tokenizer_->getAndPopPos()));
                }
                
                std::string char_code_str;
                for(int i = 0; !tokenizer_->atEnd() && i < 2; i ++){
                    c = *tokenizer_->peek().begin();
                    if(CNumberTokenParser::is_hex_digit(c)){
                        char_code_str += tokenizer_->get();
                    }else if(i == 0){
                        //tokenizer_->popPos();
                        throw(NoHexDigitsParseException(tokenizer_->getAndPopPos()));
                    }else{
                        break;
                    }
                }
                std::stringstream ss(char_code_str);
                ss.setf(std::ios::hex, std::ios::basefield);
                int c_i;
                ss >> c_i;

                token_str += static_cast<char>(c_i);
                
            }else if(c == newline_char){//\n
                tokenizer_->skip();
            }else{//esc
                const char* it = std::find(_from_esc, _from_esc + _arr_esc_size, c);
                size_t i = std::distance(_from_esc, it);

                if(i < _arr_esc_size){
                    token_str += _to_esc[i];
                    tokenizer_->skip();
                }else{//default
                    token_str += c;
                    tokenizer_->skip();
                }
            }
            cur_esc = false;
        }
    }
    tokenizer_->forgetPos();
    //std::cout << token_str << std::endl;
    return new CStringToken(_begin, _end, token_str, _id, _gid);
}

const std::string& CStringTokenParser::begin() const
{
    return _begin;
}

void CStringTokenParser::setBegin(const std::string& begin_)
{
    _begin = begin_;
}

const std::string& CStringTokenParser::end() const
{
    return _end;
}

void CStringTokenParser::setEnd(const std::string& end_)
{
    _end = end_;
}
