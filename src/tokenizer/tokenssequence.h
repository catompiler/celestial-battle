#ifndef TOKENSSEQUENCE_H
#define	TOKENSSEQUENCE_H

#include <stddef.h>
#include "token.h"
#include "tokenizer.h"
#include "tokenposition.h"


class TokensSequence
{
public:
    
    static const tokenid_t AnyToken = static_cast<tokenid_t>(-1);
    static const tokenid_t AnyTokenGroup = static_cast<tokenid_t>(-1);
    
    class Filter{
    public:
        Filter(tokenid_t id_, tokenid_t gid_, bool required_ = true);
        Filter(const Filter& filter_);
        ~Filter();
        
        tokenid_t id() const;
        void setId(tokenid_t id_);
        
        tokenid_t gid() const;
        void setGid(tokenid_t gid_);
        
        bool required() const;
        void setRequired(bool required_);
        
        bool match(const Token* token_);
        bool match(tokenid_t id_, tokenid_t gid_);
        
        Filter& operator=(const Filter& filter_);
        bool operator==(const Filter& filter_) const;
        
    private:
        tokenid_t _id;
        tokenid_t _gid;
        bool _required;
    };
    
    
    TokensSequence(const Tokenizer* tokenizer_);
    ~TokensSequence();
    
    bool atEnd() const;
    bool hasTokens() const;
    
    const TokenPosition& position() const;
    
    size_t remaining() const;
    
    bool match(Filter* sequence_, size_t count_) const;
    
    const Token* peek();
    const Token* get();
    void skip();
    void skip(size_t n_);
    
private:
    typedef Tokenizer::const_iterator iterator;
    const Tokenizer* _tokenizer;
    iterator _it_beg;
    iterator _it_cur;
    iterator _it_end;
};

#endif	/* TOKENSSEQUENCE_H */

