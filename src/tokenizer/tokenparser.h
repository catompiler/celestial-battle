#ifndef TOKENPARSER_H
#define	TOKENPARSER_H

#include "token.h"


class Tokenizer;

class TokenParser {
public:
    TokenParser(tokenid_t id_, tokenid_t gid_);
    TokenParser(const TokenParser& parser_);
    ~TokenParser();
    
    tokenid_t id() const;
    tokenid_t gid() const;
    
    virtual Token* parse(Tokenizer* tokenizer_) const = 0;
protected:
    tokenid_t _id;
    tokenid_t _gid;
};


#endif	/* TOKENPARSER_H */

