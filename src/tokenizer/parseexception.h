#ifndef PARSEEXCEPTION_H
#define	PARSEEXCEPTION_H

#include "exception/exception.h"
#include "tokenposition.h"

class ParseException
    :public Exception
{
public:
    ParseException(const TokenPosition& pos_);
    ParseException(const TokenPosition& pos_, const char* what_);
    ~ParseException() noexcept;
    
    const TokenPosition& position() const noexcept;
protected:
    TokenPosition _pos;
};

//tokenizer
class UnknownTokenParseException
    :public ParseException
{
public:
    UnknownTokenParseException(const TokenPosition& pos_);
    ~UnknownTokenParseException() noexcept;
};

//SequenceTokenParser
class NoSquenceEndParseException
    :public ParseException
{
public:
    NoSquenceEndParseException(const TokenPosition& pos_);
    ~NoSquenceEndParseException() noexcept;
};

//NumberTokenParser
class TooManyDecPointsParseException
    :public ParseException
{
public:
    TooManyDecPointsParseException(const TokenPosition& pos_);
    ~TooManyDecPointsParseException() noexcept;
};

class NoDigitsInExpParseException
    :public ParseException
{
public:
    NoDigitsInExpParseException(const TokenPosition& pos_);
    ~NoDigitsInExpParseException() noexcept;
};

class InvalitOctDigitParseException
    :public ParseException
{
public:
    InvalitOctDigitParseException(const TokenPosition& pos_);
    ~InvalitOctDigitParseException() noexcept;
};

//CStringTokenParser
class NoStringEndParseException
    :public ParseException
{
public:
    NoStringEndParseException(const TokenPosition& pos_);
    ~NoStringEndParseException() noexcept;
};

class NoHexDigitsParseException
    :public ParseException
{
public:
    NoHexDigitsParseException(const TokenPosition& pos_);
    ~NoHexDigitsParseException() noexcept;
};

#endif	/* PARSEEXCEPTION_H */

