#include "parseexception.h"



ParseException::ParseException(const TokenPosition& pos_)
    :Exception("")
{
    _pos = pos_;
}

ParseException::ParseException(const TokenPosition& pos_, const char* what_)
    :Exception(what_)
{
    _pos = pos_;
}

ParseException::~ParseException() throw()
{
}

const TokenPosition& ParseException::position() const throw()
{
    return _pos;
}

UnknownTokenParseException::UnknownTokenParseException(const TokenPosition& pos_)
    :ParseException(pos_, "Unknown token")
{
}

UnknownTokenParseException::~UnknownTokenParseException() throw()
{
}

NoSquenceEndParseException::NoSquenceEndParseException(const TokenPosition& pos_)
    :ParseException(pos_, "No end of the sequence")
{
}

NoSquenceEndParseException::~NoSquenceEndParseException() throw()
{
}

TooManyDecPointsParseException::TooManyDecPointsParseException(const TokenPosition& pos_)
    :ParseException(pos_, "Too many decimal points")
{
}

TooManyDecPointsParseException::~TooManyDecPointsParseException() throw()
{
}


NoDigitsInExpParseException::NoDigitsInExpParseException(const TokenPosition& pos_)
    :ParseException(pos_, "No digits in the exponent")
{
}

NoDigitsInExpParseException::~NoDigitsInExpParseException() throw()
{
}


InvalitOctDigitParseException::InvalitOctDigitParseException(const TokenPosition& pos_)
    :ParseException(pos_, "Bad oct digit")
{
}

InvalitOctDigitParseException::~InvalitOctDigitParseException() throw()
{
}


NoStringEndParseException::NoStringEndParseException(const TokenPosition& pos_)
    :ParseException(pos_, "No end of the string")
{
}

NoStringEndParseException::~NoStringEndParseException() throw()
{
}


NoHexDigitsParseException::NoHexDigitsParseException(const TokenPosition& pos_)
    :ParseException(pos_, "No hex digits after \\x")
{
}

NoHexDigitsParseException::~NoHexDigitsParseException() throw()
{
}