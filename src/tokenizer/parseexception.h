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
    ~ParseException() throw();
    
    const TokenPosition& position() const throw();
protected:
    TokenPosition _pos;
};

//tokenizer
class UnknownTokenParseException
    :public ParseException
{
public:
    UnknownTokenParseException(const TokenPosition& pos_);
    ~UnknownTokenParseException() throw();
};

//SequenceTokenParser
class NoSquenceEndParseException
    :public ParseException
{
public:
    NoSquenceEndParseException(const TokenPosition& pos_);
    ~NoSquenceEndParseException() throw();
};

//NumberTokenParser
class TooManyDecPointsParseException
    :public ParseException
{
public:
    TooManyDecPointsParseException(const TokenPosition& pos_);
    ~TooManyDecPointsParseException() throw();
};

class NoDigitsInExpParseException
    :public ParseException
{
public:
    NoDigitsInExpParseException(const TokenPosition& pos_);
    ~NoDigitsInExpParseException() throw();
};

class InvalitOctDigitParseException
    :public ParseException
{
public:
    InvalitOctDigitParseException(const TokenPosition& pos_);
    ~InvalitOctDigitParseException() throw();
};

//CStringTokenParser
class NoStringEndParseException
    :public ParseException
{
public:
    NoStringEndParseException(const TokenPosition& pos_);
    ~NoStringEndParseException() throw();
};

class NoHexDigitsParseException
    :public ParseException
{
public:
    NoHexDigitsParseException(const TokenPosition& pos_);
    ~NoHexDigitsParseException() throw();
};

#endif	/* PARSEEXCEPTION_H */

