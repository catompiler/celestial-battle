#include "configexception.h"


ConfigException::ConfigException(const TokenPosition& pos_)
    :ParseException(pos_, "")
{
}

ConfigException::ConfigException(const TokenPosition& pos_, const char* what_) throw()
    :ParseException(pos_, what_)
{
}

ConfigException::~ConfigException() throw()
{
}

//Unexpected end of config
UnexpectedConfigEnd::UnexpectedConfigEnd(const TokenPosition& pos_)
    :ConfigException(pos_, "Bad number parameter")
{
}

UnexpectedConfigEnd::~UnexpectedConfigEnd() throw()
{
}

//BadNumberParameter
BadNumberParameter::BadNumberParameter(const TokenPosition& pos_)
    :ConfigException(pos_, "Bad number parameter")
{
}

BadNumberParameter::~BadNumberParameter() throw()
{
}

//UnknownParameterType
UnknownParameterType::UnknownParameterType(const TokenPosition& pos_)
    :ConfigException(pos_, "Unknown parameter type")
{
}

UnknownParameterType::~UnknownParameterType() throw()
{
}

//Expected separator
ExpectedSeparator::ExpectedSeparator(const TokenPosition& pos_)
    :ConfigException(pos_, "Expected separator (\";\" or \",\")")
{
}

ExpectedSeparator::~ExpectedSeparator() throw()
{
}

//ExpectedGroupDeclaration
ExpectedGroupDeclaration::ExpectedGroupDeclaration(const TokenPosition& pos_)
    :ConfigException(pos_, "Expected group declaration")
{
}

ExpectedGroupDeclaration::~ExpectedGroupDeclaration() throw()
{
}

//UnknownDeclaration
UnknownDeclaration::UnknownDeclaration(const TokenPosition& pos_)
    :ConfigException(pos_, "Unknown declaration")
{
}

UnknownDeclaration::~UnknownDeclaration() throw()
{
}

//InvalidParametersList
InvalidParametersList::InvalidParametersList(const TokenPosition& pos_)
    :ConfigException(pos_, "Invalid parameters list")
{
}

InvalidParametersList::~InvalidParametersList() throw()
{
}

//InvalidParametersCount
InvalidParametersCount::InvalidParametersCount(const TokenPosition& pos_)
    :ConfigException(pos_, "Invalid parameters count")
{
}

InvalidParametersCount::~InvalidParametersCount() throw()
{
}




