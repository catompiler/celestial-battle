#ifndef TOKENIZER_H
#define	TOKENIZER_H

#include "tokenposition.h"
#include <string>
#include <stddef.h>
#include <stack>
#include <list>
#include <utility>
#include <map>
#include <functional>


class Token;
class TokenParser;

typedef unsigned int tokenprior_t;

class Tokenizer {
public:
    
    Tokenizer();
    ~Tokenizer();
    
    const std::string& source() const;
    void setSource(const std::string& source_);
    
    bool skipUnknownTokens() const;
    void setSkipUnknownTokens(bool skip_);
    
    bool parse(const std::string& source_);
    bool parse();
    
    typedef std::list<Token*> Tokens;
    typedef Tokens::iterator iterator;
    typedef Tokens::const_iterator const_iterator;
    void clearTokens();
    void removeToken(iterator pos_);
    iterator tokensBegin();
    iterator tokensEnd();
    const_iterator tokensBegin() const;
    const_iterator tokensEnd() const;

    bool hasTokenParser(const TokenParser* tokenparser_);
    bool addTokenParser(tokenprior_t prior_, const TokenParser* tokenparser_);
    bool delTokenParser(const TokenParser* tokenparser_);
    void clearTokenParsers();
    
    std::string peek() const;
    std::string peek(size_t count_) const;
    
    std::string get();
    std::string get(size_t count_);
    
    void pushPos();
    bool popPos();
    TokenPosition getAndPopPos();
    void forgetPos();
    
    const TokenPosition& position() const;
    
    bool skip();
    bool skip(size_t count_);
    
    bool atEnd() const;
    
    size_t remaining() const;
    
    size_t line() const;
    size_t col() const;
    size_t offset() const;
    
private:
    std::string _source;
    
    bool _skip_unknown_tokens;
    
    struct Posit : TokenPosition{
        
        Posit() : TokenPosition(), it_cur()
        {}
        
        Posit(size_t offset_, size_t line_,
              size_t col_, std::string::iterator it_cur_)
                : TokenPosition(offset_, line_, col_), it_cur(it_cur_)
        {}
        
        Posit(const Posit& pos_) : TokenPosition(pos_), it_cur(pos_.it_cur)
        {}
        
        ~Posit(){}
        
        Posit& operator=(const Posit& pos_){
            TokenPosition::operator =(pos_);
            it_cur = pos_.it_cur;
            return *this;
        }
        
        bool operator==(const Posit& pos_){
            return TokenPosition::operator ==(pos_) && it_cur == pos_.it_cur;
        }
        
        std::string::iterator it_cur;
    };
    
    typedef std::stack<Posit> Positions;
    
    Posit _pos;
    Positions* _positions;
    
    struct priorcmp{
        bool operator()(tokenprior_t l, tokenprior_t r){
            return r == 0 ? false : l > r;
        }
    };
    typedef std::multimap<tokenprior_t, const TokenParser*, priorcmp/*std::greater<tokenprior_t>*/> TokenParsers;
    TokenParsers* _parsers;
    
    //typedef std::list<Token*> Tokens;
    Tokens* _tokens;
    
    void _addToken(Token* token_);
    Token* _nexToken();
};

#endif	/* TOKENIZER_H */

