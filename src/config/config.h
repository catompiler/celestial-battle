#ifndef _CONFIG_H
#define	_CONFIG_H

#include <string>
#include <vector>
#include <istream>
#include <list>


typedef std::string::iterator iterator_t;
typedef std::string::value_type value_t;

void debug_print(iterator_t begin, iterator_t end);

//! skip white-spaces
iterator_t skip_ws(iterator_t begin, iterator_t end);
//! skip comment, defined by comment_begin and comment_end
iterator_t skip_comment(const std::string& comment_begin,
                        const std::string comment_end,
                        iterator_t begin, iterator_t end);
//! skip c-style comment
iterator_t skip_c_comment(iterator_t begin, iterator_t end);
//! skip cpp-style comment
iterator_t skip_cpp_comment(iterator_t begin, iterator_t end);
//! skip all styles comments
iterator_t skip_comments(iterator_t begin, iterator_t end);
//! skip all trash data
iterator_t skip_trash(iterator_t begin, iterator_t end);

//! is name character
bool isnamechar(value_t c, bool isfirst = false);
//! try to find sign after name
bool isit(const std::string& sign, iterator_t begin, iterator_t end);
//! read name
iterator_t get_name(std::string& name, iterator_t begin, iterator_t end);

class Element{
public:
    virtual ~Element();
    virtual iterator_t parse(iterator_t config_begin, iterator_t config_end) = 0;
    
    static const std::string line_sep;
};

class NamedElement
    :public Element
{
public:
    NamedElement(const std::string& name_);
    const std::string& name() const;
protected:
    std::string _name;
};

class Value;
class ValueBase
    :public Element
{
public:
    
    ValueBase();
    ~ValueBase();
    
    virtual int getInt(bool* isOk = NULL) const;
    virtual bool getBool(bool* isOk = NULL) const;
    virtual double getDouble(bool* isOk = NULL) const;
    virtual std::string getRaw(bool* isOk = NULL) const;
    virtual std::string getString(bool* isOk = NULL) const;
    virtual std::vector<Value> getVector(bool* isOk = NULL) const;

    virtual bool set(int val_);
    virtual bool set(bool val_);
    virtual bool set(double val_);
    virtual bool setRaw(const std::string& val_);
    virtual bool set(const std::string& val_);
    virtual bool set(const std::vector<Value>& val_);
    
    iterator_t parse(iterator_t config_begin, iterator_t config_end);
};

class Value
    :public ValueBase
{
public:
    
    Value();
    ~Value();
    
    int getInt(bool* isOk = NULL) const;
    bool getBool(bool* isOk = NULL) const;
    double getDouble(bool* isOk = NULL) const;
    std::string getRaw(bool* isOk = NULL) const;
    std::string getString(bool* isOk = NULL) const;
    std::vector<Value> getVector(bool* isOk = NULL) const;

    bool set(int val_);
    bool set(bool val_);
    bool set(double val_);
    bool setRaw(const std::string& val_);
    bool set(const std::string& val_);
    bool set(const std::vector<Value>& val_);
    
    iterator_t parse(iterator_t config_begin, iterator_t config_end);
    
private:
    
    ValueBase* _value;
};

class ValueNumber
    :public ValueBase
{
public:
    
    ValueNumber();
    ValueNumber(int val_);
    ValueNumber(double val_);
    ~ValueNumber();
    
    int getInt(bool* isOk = NULL) const;
    double getDouble(bool* isOk = NULL) const;

    bool set(int val_);
    bool set(double val_);
    
    iterator_t parse(iterator_t config_begin, iterator_t config_end);
    
    static bool isit(iterator_t config_begin, iterator_t config_end);
    
private:
    
    static const std::string _valid_number_chars;
    static const std::string _only_double_chars;
    static const std::string _single_chars;
    
    static bool isnumberchar(value_t c);
    
    bool _is_double;
    union{
        int _valuei;
        double _valued;
    };
};

class ValueBool
    :public ValueBase
{
public:
    
    ValueBool();
    ValueBool(bool val_);
    ~ValueBool();
    
    bool getBool(bool* isOk = NULL) const;
    
    bool set(bool val_);
    
    iterator_t parse(iterator_t config_begin, iterator_t config_end);
    
    static bool isit(iterator_t config_begin, iterator_t config_end);

private:
    
    static const std::string _str_true;
    static const std::string _str_false;
    
    bool _value;
};

class ValueRaw
    :public ValueBase
{
public:
    
    ValueRaw();
    ValueRaw(const std::string& val_);
    ~ValueRaw();
    
    std::string getRaw(bool* isOk = NULL) const;

    bool setRaw(const std::string& val_);
    
    iterator_t parse(iterator_t config_begin, iterator_t config_end);
    
    static bool isit(iterator_t config_begin, iterator_t config_end);
    
private:
    std::string _value;
};

class ValueString
    :public ValueBase
{
public:
    
    ValueString();
    ValueString(const std::string& val_);
    ~ValueString();
    
    std::string getString(bool* isOk = NULL) const;

    bool set(const std::string& val_);
    
    iterator_t parse(iterator_t config_begin, iterator_t config_end);
    
    static bool isit(iterator_t config_begin, iterator_t config_end);
    
private:
    std::string _value;
};

class ValueVector
    :public ValueBase
{
public:
    
    ValueVector();
    ValueVector(const std::vector<Value>& val_);
    ~ValueVector();
    
    std::vector<Value> getVector(bool* isOk = NULL) const;

    bool set(const std::vector<Value>& val_);
    
    iterator_t parse(iterator_t config_begin, iterator_t config_end);
    
    static bool isit(iterator_t config_begin, iterator_t config_end);
    
private:
    std::vector<Value> _value;
};


class Parameter
    :public NamedElement
{
public:
    
    Parameter(const std::string& name_);
    ~Parameter();
    
    Value& value();
    
    static bool isit(iterator_t begin, iterator_t end);
    iterator_t parse(iterator_t config_begin, iterator_t config_end);
    
private:
    static const std::string _parameter_sign;
    
    Value* _value;
};

class Group
    :public NamedElement
{
public:
    
    Group();
    Group(const std::string& name_);
    ~Group();
    
    Group& getGroup(const std::string& group_);
    Parameter& getParameter(const std::string& param_);
    
    static bool isit(iterator_t begin, iterator_t end);
    iterator_t parse(iterator_t config_begin, iterator_t config_end);
    
private:
    
    static const std::string _group_begin;
    static const std::string _group_end;
    static const std::string _group_sign;
    
    typedef std::list<Group*> Groups;
    typedef std::list<Parameter*> Parameters;
    
    void _def_ctor();
    
    bool _is_root;
    
    Groups* _groups;
    Parameters* _parameters;
};

class Config
{
public:
    Config();
    ~Config();
    
    bool read(std::istream& ist_);
    iterator_t parse(iterator_t config_begin, iterator_t config_end);
    
private:
    Group* _root;
};

#endif	/* _CONFIG_H */

