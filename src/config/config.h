#ifndef _CONFIG_H
#define	_CONFIG_H

#include <vector>
#include "string/string.h"

struct element_type{enum value{Parameter=0, Group};};
typedef element_type::value element_type_t;

struct value_type{enum value{Number=0, String, Vector};};
typedef value_type::value value_type_t;

class Value;
typedef std::vector<Value*> Vector;

class Config
{
public:
    Config();
    ~Config();
private:
    
class BaseElement{
public:
    virtual ~Element(){}
protected:
};

class Element
    :public BaseElement
{
public:
    virtual ~Element(){}
protected:
    BaseElement* _element;
};

class Group
    :public BaseElement
{
public:
    virtual ~Group(){}
protected:
    typedef std::vector<Element*> Elements;
    Elements* _elements;
};

class Parameter
    :public BaseElement
{
public:
    virtual ~Parameter(){}
protected:
    Value* _value;
};


class BaseValue{
public:
    virtual ~Value(){}
protected:
};

class Value
    :public BaseValue
{
public:
    virtual ~Value(){}
protected:
    BaseValue* _value;
};

class ValueNumber
    :public BaseValue
{
public:
    virtual ~ValueNumber(){}
protected:
    double _value;
};

class ValueString
    :public BaseValue
{
public:
    virtual ~ValueString(){}
protected:
    String _value;
};

class ValueVector
    :public BaseValue
{
public:
    virtual ~ValueVector(){}
protected:
    Vector _value;
};

};

#endif	/* _CONFIG_H */

