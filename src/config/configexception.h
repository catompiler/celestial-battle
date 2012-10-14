#ifndef CONFIGEXCEPTION_H
#define	CONFIGEXCEPTION_H

#include "tokenizer/parseexception.h"

class Token;


class ConfigException
    :public ParseException {
public:
    ConfigException(const TokenPosition& pos_);
    ConfigException(const TokenPosition& pos_, const char* what_) throw();
    ~ConfigException() throw();
};


class UnexpectedConfigEnd
    :public ConfigException
{
public:
    UnexpectedConfigEnd(const TokenPosition& pos_);
    ~UnexpectedConfigEnd() throw();
};


class BadNumberParameter
    :public ConfigException
{
public:
    BadNumberParameter(const TokenPosition& pos_);
    ~BadNumberParameter() throw();
};

class UnknownParameterType
    :public ConfigException
{
public:
    UnknownParameterType(const TokenPosition& pos_);
    ~UnknownParameterType() throw();
};

class ExpectedSeparator
    :public ConfigException
{
public:
    ExpectedSeparator(const TokenPosition& pos_);
    ~ExpectedSeparator() throw();
};

class ExpectedGroupDeclaration
    :public ConfigException
{
public:
    ExpectedGroupDeclaration(const TokenPosition& pos_);
    ~ExpectedGroupDeclaration() throw();
};

class UnknownDeclaration
    :public ConfigException
{
public:
    UnknownDeclaration(const TokenPosition& pos_);
    ~UnknownDeclaration() throw();
};

class InvalidParametersList
    :public ConfigException
{
public:
    InvalidParametersList(const TokenPosition& pos_);
    ~InvalidParametersList() throw();
};

class InvalidParametersCount
    :public ConfigException
{
public:
    InvalidParametersCount(const TokenPosition& pos_);
    ~InvalidParametersCount() throw();
};

#endif	/* CONFIGEXCEPTION_H */

