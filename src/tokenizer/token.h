#ifndef TOKEN_H
#define	TOKEN_H

#include <string>
#include "tokenposition.h"

typedef int tokenid_t;

class Token {
public:
    Token(tokenid_t id_, tokenid_t gid_);
    Token(const Token& token_);
    virtual ~Token();
    
    virtual Token* clone() const = 0;
    
    tokenid_t id() const;
    tokenid_t gid() const;
    
    virtual std::string toString() const = 0;
    virtual std::string value() const = 0;
    
    const TokenPosition& pos() const;
    TokenPosition& pos();
    void setPos(const TokenPosition& pos_);
    
protected:
    tokenid_t _id;
    tokenid_t _gid;
    TokenPosition _pos;
};

#endif	/* TOKEN_H */

