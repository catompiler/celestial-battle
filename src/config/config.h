#ifndef _CONFIG_H
#define	_CONFIG_H

#include <string>
#include <vector>


class Element{
public:
};

class NamedElement
    :public Element
{
public:
    const std::string& name() const;
};

class Value
    :public Element
{
public:
    int getInt() const;
    bool getBool() const;
    double getDouble() const;
    std::string getString() const;
    std::vector<Value> getVector() const;

    void set(int val_);
    void set(bool val_);
    void set(double val_);
    void set(const std::string& val_);
    void set(const std::vector<Value>& val_);
};

class Parameter
    :public NamedElement
{
public:
    Value& value();
};

class Group
    :public NamedElement
{
public:
    Group& getGroup(const std::string& group_);
    Parameter& getParameter(const std::string& param_);
};

class Config
{
public:
    Config();
    ~Config();
};

#endif	/* _CONFIG_H */

