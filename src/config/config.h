#ifndef _CONFIG_H
#define	_CONFIG_H


class ConfigElement{
public:
    virtual ~ConfigElement(){};
protected:
    struct element_type{enum value{Parameter=0, Group, Value};};
    typedef element_type::value element_type_t;
};

class ConfigParameter
    :public ConfigElement
{
public:
    ~ConfigParameter(){};
};

class ConfigGroup
    :public ConfigElement
{
public:
    ~ConfigGroup(){};
};

class ConfigValue
    :public ConfigElement
{
public:
    ~ConfigValue(){};
protected:
    struct value_type{enum value{Number=0, String, Vector};};
    typedef value_type::value value_type_t;
};

class ConfigValueNumber
    :public ConfigValue
{
public:
    ~ConfigValueNumber(){};
};

class ConfigValueString
    :public ConfigValue
{
public:
    ~ConfigValueString(){};
};

class ConfigValueVector
    :public ConfigValue
{
public:
    ~ConfigValueVector(){};
};


class Config
    :public ConfigGroup
{
public:
    Config();
    ~Config();
private:
};

#endif	/* _CONFIG_H */

