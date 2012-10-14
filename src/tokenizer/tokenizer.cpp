#include "tokenizer.h"
#include "tokenparser.h"
#include "token.h"
#include "utils/utils.h"
#include "parseexception.h"
#include <algorithm>
#include <iterator>
#include <utility>



Tokenizer::Tokenizer() {
    _positions = new Positions();
    _parsers = new TokenParsers();
    _tokens = new Tokens();
    _pos.reset();
    _pos.it_cur = _source.begin();
    _skip_unknown_tokens = false;
}

Tokenizer::~Tokenizer() {
    functions::delete_all(_tokens); delete _tokens;
    /*functions::delete_all(_parsers);*/ delete _parsers;
    /*functions::delete_all(_positions);*/ delete _positions;
}

const std::string& Tokenizer::source() const
{
    return _source;
}

void Tokenizer::setSource(const std::string& source_)
{
    _source = source_;
    _pos.reset();
    _pos.it_cur = _source.begin();
}

bool Tokenizer::skipUnknownTokens() const
{
    return _skip_unknown_tokens;
}

void Tokenizer::setSkipUnknownTokens(bool skip_)
{
    _skip_unknown_tokens = skip_;
}

bool Tokenizer::parse(const std::string& source_)
{
    setSource(source_);
    return parse();
}

bool Tokenizer::parse()
{
    clearTokens();
    
    Token* token = NULL;
    
    while(!atEnd()){
        token = _nexToken();
        if(token){
            token->setPos(_pos);
            _addToken(token);
        }else{
            if(_skip_unknown_tokens)
                skip();
            else
                throw(UnknownTokenParseException(position()));
                //break;
        }
    }
    return atEnd();
}

void Tokenizer::clearTokens()
{
    functions::delete_all(_tokens); _tokens->clear();
}

void Tokenizer::removeToken(iterator pos_)
{
    delete *pos_;
    _tokens->erase(pos_);
}

Tokenizer::iterator Tokenizer::tokensBegin()
{
    return _tokens->begin();
}

Tokenizer::iterator Tokenizer::tokensEnd()
{
    return _tokens->end();
}

Tokenizer::const_iterator Tokenizer::tokensBegin() const
{
    return _tokens->begin();
}

Tokenizer::const_iterator Tokenizer::tokensEnd() const
{
    return _tokens->end();
}


bool Tokenizer::hasTokenParser(const TokenParser* tokenparser_)
{
    TokenParsers::iterator it = std::find_if(_parsers->begin(), _parsers->end(),
                                    functors::make_value_equal(tokenparser_));
    return it != _parsers->end();
}

bool Tokenizer::addTokenParser(tokenprior_t prior_, const TokenParser* tokenparser_)
{
    if(hasTokenParser(tokenparser_)) return false;
    _parsers->insert(std::make_pair(prior_, tokenparser_));
    return true;
}

bool Tokenizer::delTokenParser(const TokenParser* tokenparser_)
{
    bool deleted = false;
    functors::value_equal<const TokenParser*> valuecmp = functors::make_value_equal(tokenparser_);
    for(;;){
        TokenParsers::iterator it = std::find_if(_parsers->begin(), _parsers->end(), valuecmp);
        if(it == _parsers->end()) break;
        _parsers->erase(it);
        deleted = true;
    }
    return deleted;
}

void Tokenizer::clearTokenParsers()
{
    _parsers->clear();
}

std::string Tokenizer::peek() const
{
    if(_pos.it_cur == _source.end()) return std::string();
    std::string::iterator it2(_pos.it_cur); ++ it2;
    return std::string(_pos.it_cur, it2);
}

std::string Tokenizer::peek(size_t count_) const
{
    if(remaining() < count_) return std::string();
    std::string::iterator it2(_pos.it_cur);
    std::advance(it2, count_);
    return std::string(_pos.it_cur, it2);
}

std::string Tokenizer::get()
{
    std::string::iterator it2(_pos.it_cur);
    if(!skip()) return std::string();
    return std::string(it2, _pos.it_cur);
}
std::string Tokenizer::get(size_t count_)
{
    std::string::iterator it2(_pos.it_cur);
    if(!skip(count_)) return std::string();
    return std::string(it2, _pos.it_cur);
}

void Tokenizer::pushPos()
{
    _positions->push(_pos);
}

bool Tokenizer::popPos()
{
    if(_positions->empty()) return false;
    _pos = _positions->top(); _positions->pop();
    return true;
}

TokenPosition Tokenizer::getAndPopPos()
{
    if(_positions->empty()) return _pos;
    
    TokenPosition res = _pos;
    _pos = _positions->top(); _positions->pop();
    return res;
}

void Tokenizer::forgetPos()
{
    if(!_positions->empty()) _positions->pop();
}

const TokenPosition& Tokenizer::position() const
{
    return _pos;
}

bool Tokenizer::skip()
{
    if(_pos.it_cur == _source.end()) return false;
    
    _pos.incOffset();//_pos.offset ++;
    if(*_pos.it_cur == '\n'){
        _pos.incLine();//_pos.line ++;
        _pos.setCol(0);//_pos.col = 0;
    }else{
        _pos.incCol();//_pos.col ++;
    }
    ++_pos.it_cur;
    
    return true;
}

bool Tokenizer::skip(size_t count_)
{
    if(remaining() < count_) return false;
    for(int i = 0; i < count_; i ++) skip();
    return true;
}

bool Tokenizer::atEnd() const
{
    return _pos.it_cur == _source.end();
}

size_t Tokenizer::remaining() const
{
    std::string::const_iterator it2 = _source.end();
    return std::distance<std::string::const_iterator>(_pos.it_cur, it2);
}

size_t Tokenizer::line() const
{
    return _pos.line();
}

size_t Tokenizer::col() const
{
    return _pos.col();
}

size_t Tokenizer::offset() const
{
    return _pos.offset();
}

void Tokenizer::_addToken(Token* token_)
{
    _tokens->push_back(token_);
}

Token* Tokenizer::_nexToken()
{
    Token* res_token = NULL;
    for(TokenParsers::iterator it = _parsers->begin(); it != _parsers->end(); ++ it){
        res_token = (*it).second->parse(this);
        if(res_token != NULL){
            break;
        }
    }
    return res_token;
}
