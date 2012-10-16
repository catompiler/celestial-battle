#include "token.h"


//Token

Token::Token(tokenid_t id_, tokenid_t gid_)
{
    _id = id_;
    _gid = gid_;
}

Token::Token(const Token& token_)
{
    _id = token_._id;
    _gid = token_._gid;
}

Token::~Token()
{
}

tokenid_t Token::id() const
{
    return _id;
}

tokenid_t Token::gid() const
{
    return _gid;
}

const TokenPosition& Token::pos() const
{
    return _pos;
}

TokenPosition& Token::pos()
{
    return _pos;
}

void Token::setPos(const TokenPosition& pos_)
{
    _pos = pos_;
}


