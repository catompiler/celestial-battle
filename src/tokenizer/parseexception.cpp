#include "parseexception.h"



ParseException::ParseException(const TokenPosition& pos_)
    :Exception()
{
    _pos = pos_;
}

ParseException::ParseException(const TokenPosition& pos_, const char* what_)
    :Exception(what_)
{
    _pos = pos_;
}

ParseException::~ParseException() noexcept
{
}

const TokenPosition& ParseException::position() const noexcept
{
    return _pos;
}

UnknownTokenParseException::UnknownTokenParseException(const TokenPosition& pos_)
    :ParseException(pos_, "Unknown token")
{
}

UnknownTokenParseException::~UnknownTokenParseException() noexcept
{
}

NoSquenceEndParseException::NoSquenceEndParseException(const TokenPosition& pos_)
    :ParseException(pos_, "No end of the sequence")
{
}

NoSquenceEndParseException::~NoSquenceEndParseException() noexcept
{
}

TooManyDecPointsParseException::TooManyDecPointsParseException(const TokenPosition& pos_)
    :ParseException(pos_, "Too many decimal points")
{
}

TooManyDecPointsParseException::~TooManyDecPointsParseException() noexcept
{
}


NoDigitsInExpParseException::NoDigitsInExpParseException(const TokenPosition& pos_)
    :ParseException(pos_, "No digits in the exponent")
{
}

NoDigitsInExpParseException::~NoDigitsInExpParseException() noexcept
{
}


InvalitOctDigitParseException::InvalitOctDigitParseException(const TokenPosition& pos_)
    :ParseException(pos_, "Bad oct digit")
{
}

InvalitOctDigitParseException::~InvalitOctDigitParseException() noexcept
{
}


NoStringEndParseException::NoStringEndParseException(const TokenPosition& pos_)
    :ParseException(pos_, "No end of the string")
{
}

NoStringEndParseException::~NoStringEndParseException() noexcept
{
}


NoHexDigitsParseException::NoHexDigitsParseException(const TokenPosition& pos_)
    :ParseException(pos_, "No hex digits after \\x")
{
}

NoHexDigitsParseException::~NoHexDigitsParseException() noexcept
{
}