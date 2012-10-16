#include "tokenparser.h"


//TokenParser

TokenParser::TokenParser(tokenid_t id_, tokenid_t gid_)
{
    _id = id_;
    _gid = gid_;
}

TokenParser::TokenParser(const TokenParser& parser_)
{
    _id = parser_._id;
    _gid = parser_._gid;
}

TokenParser::~TokenParser()
{
}

tokenid_t TokenParser::id() const
{
    return _id;
}

tokenid_t TokenParser::gid() const
{
    return _gid;
}

