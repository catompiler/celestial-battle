#include "config.h"
#include <iterator>
#include <iostream>
#include <functional>
#include <algorithm>
#include <ctype.h>
#include <stdlib.h>
#include "utils/utils.h"


void debug_print(iterator_t begin, iterator_t end)
{
    std::ostreambuf_iterator<char> out_it(std::cout);
    std::copy(begin, end, out_it);
    std::cout << std::endl;
}


iterator_t skip_ws(iterator_t begin, iterator_t end)
{
    return std::find_if(begin, end, std::not1(std::ptr_fun(isspace)));
}

iterator_t skip_comment(const std::string& comment_begin,
                        const std::string comment_end,
                        iterator_t begin, iterator_t end)
{
    if(comment_begin.length() > std::distance(end,begin)) return begin;
    if(std::equal(comment_begin.begin(), comment_begin.end(), begin)){
        begin = std::search(begin, end, comment_end.begin(), comment_end.end());
        if(end - begin >= comment_end.length()) std::advance(begin, comment_end.length());
    }
    return begin;
}

iterator_t skip_c_comment(iterator_t begin, iterator_t end)
{
    static std::string comment_begin = "/*";
    static std::string comment_end = "*/";
    
    return skip_comment(comment_begin, comment_end, begin, end);
}

iterator_t skip_cpp_comment(iterator_t begin, iterator_t end)
{
    static std::string comment_begin = "//";
    static std::string comment_end = "\n";
    
    return skip_comment(comment_begin, comment_end, begin, end);
}

iterator_t skip_comments(iterator_t begin, iterator_t end)
{
    iterator_t res_c, res_cpp;
    
    for(;; begin != end){
        res_c = skip_c_comment(begin, end);
        res_cpp = skip_cpp_comment(begin, end);
        
        if(res_c == begin && res_cpp == begin) break;
        
        begin = std::max(res_c, res_cpp);
    }
    return begin;
}

iterator_t skip_trash(iterator_t begin, iterator_t end)
{
    iterator_t res_comments, res_ws;
    
    for(;; begin != end){
        res_comments = skip_comments(begin, end);
        res_ws = skip_ws(begin, end);
        
        if(res_comments == begin && res_ws == begin) break;
        
        begin = std::max(res_comments, res_ws);
    }
    return begin;
}

bool isnamechar(value_t c, bool isfirst)
{
    return isalpha(c) || (isfirst == true ? false : isdigit(c)) || c == '_';
}

bool isit(const std::string& sign, iterator_t begin, iterator_t end)
{
    begin = skip_trash(begin, end);
    begin = std::find_if(begin, end, std::not1(
                            std::bind2nd(
                            std::ptr_fun(isnamechar), false)));
    begin = skip_trash(begin, end);
    if(sign.length() > std::distance(end, begin)) return false;
    return std::equal(sign.begin(), sign.end(), begin);
}

iterator_t get_name(std::string& name, iterator_t begin, iterator_t end)
{
    begin = skip_trash(begin, end);
 
    //if first char of name not valid
    if(isnamechar(*begin, true) == false) return begin;
    
    //find first not name char
    iterator_t end_name = std::find_if(begin, end, std::not1(
                                        std::bind2nd(
                                        std::ptr_fun(isnamechar), false)));
    
    name = std::string(begin, end_name);
    
    return end_name;
}


const std::string Element::line_sep = ";";

Element::~Element()
{
}


NamedElement::NamedElement(const std::string& name_)
        :Element()
{
    _name = name_;
}

const std::string& NamedElement::name() const
{
    return _name;
}



ValueBase::ValueBase()
{
}

ValueBase::~ValueBase()
{
}

int ValueBase::getInt(bool* isOk) const
{
    if(isOk) *isOk = false;
    return 0;
}

bool ValueBase::getBool(bool* isOk) const
{
    if(isOk) *isOk = false;
    return false;
}

double ValueBase::getDouble(bool* isOk) const
{
    if(isOk) *isOk = false;
    return 0.0;
}

std::string ValueBase::getRaw(bool* isOk) const
{
    if(isOk) *isOk = false;
    return std::string();
}

std::string ValueBase::getString(bool* isOk) const
{
    if(isOk) *isOk = false;
    return std::string();
}

std::vector<Value> ValueBase::getVector(bool* isOk) const
{
    if(isOk) *isOk = false;
    return std::vector<Value>();
}

bool ValueBase::set(int)
{
    return false;
}

bool ValueBase::set(bool)
{
    return false;
}

bool ValueBase::set(double)
{
    return false;
}

bool ValueBase::setRaw(const std::string&)
{
    return false;
}

bool ValueBase::set(const std::string&)
{
    return false;
}

bool ValueBase::set(const std::vector<Value>&)
{
    return false;
}

iterator_t ValueBase::parse(iterator_t config_begin, iterator_t config_end)
{
    return config_begin;
}


Value::Value()
{
    _value = NULL;
}

Value::~Value()
{
    delete _value;
}

int Value::getInt(bool* isOk) const
{
    if(_value == NULL) return ValueBase::getInt(isOk);
    return _value->getInt(isOk);
}

bool Value::getBool(bool* isOk) const
{
    if(_value == NULL) return ValueBase::getBool(isOk);
    return _value->getBool(isOk);
}

double Value::getDouble(bool* isOk) const
{
    if(_value == NULL) return ValueBase::getDouble(isOk);
    return _value->getDouble(isOk);
}

std::string Value::getRaw(bool* isOk) const
{
    if(_value == NULL) return ValueBase::getRaw(isOk);
    return _value->getRaw(isOk);
}

std::string Value::getString(bool* isOk) const
{
    if(_value == NULL) return ValueBase::getString(isOk);
    return _value->getString(isOk);
}

std::vector<Value> Value::getVector(bool* isOk) const
{
    if(_value == NULL) return ValueBase::getVector(isOk);
    return _value->getVector(isOk);
}


bool Value::set(int val_)
{
    if(_value == NULL){
        return ValueBase::set(val_);
    }else if(!_value->set(val_)){
        delete _value;
        _value = new ValueNumber(val_);
    }
    return true;
}

bool Value::set(bool val_)
{
    if(_value == NULL){
        return ValueBase::set(val_);
    }else if(!_value->set(val_)){
        delete _value;
        _value = new ValueBool(val_);
    }
    return true;
}

bool Value::set(double val_)
{
    if(_value == NULL){
        return ValueBase::set(val_);
    }else if(!_value->set(val_)){
        delete _value;
        _value = new ValueNumber(val_);
    }
    return true;
}

bool Value::setRaw(const std::string& val_)
{
    if(_value == NULL){
        return ValueBase::setRaw(val_);
    }else if(!_value->setRaw(val_)){
        delete _value;
        _value = new ValueRaw(val_);
    }
    return true;
}

bool Value::set(const std::string& val_)
{
    if(_value == NULL){
        return ValueBase::set(val_);
    }else if(!_value->set(val_)){
        delete _value;
        _value = new ValueString(val_);
    }
    return true;
}

bool Value::set(const std::vector<Value>& val_)
{
    if(_value == NULL){
        return ValueBase::set(val_);
    }else if(!_value->set(val_)){
        delete _value;
        _value = new ValueVector(val_);
    }
    return true;
}

iterator_t Value::parse(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    
    if(ValueNumber::isit(current, config_end)){
        _value = new ValueNumber;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current) return config_begin;
        return current;
    }else if(ValueString::isit(current, config_end)){
        _value = new ValueString;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current) return config_begin;
        return current;
    }else if(ValueVector::isit(current, config_end)){
        _value = new ValueVector;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current) return config_begin;
        return current;
    }else if(ValueBool::isit(current, config_end)){
        _value = new ValueBool;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current) return config_begin;
        return current;
    }else if(ValueRaw::isit(current, config_end)){
        _value = new ValueRaw;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current) return config_begin;
        return current;
    }
    
    return config_begin;
}


const std::string ValueNumber::_valid_number_chars = "xXeE-+.0123456789aAbBcCdDeEfF";
const std::string ValueNumber::_only_double_chars = ".eE";
const std::string ValueNumber::_single_chars = "-+eExX.";

ValueNumber::ValueNumber()
{
    _is_double = false;
    _valuei = 0;
}

ValueNumber::ValueNumber(int val_)
{
    _is_double = false;
    _valuei = val_;
}

ValueNumber::ValueNumber(double val_)
{
    _is_double = true;
    _valued = val_;
}

ValueNumber::~ValueNumber()
{
}

int ValueNumber::getInt(bool* isOk) const
{
    if(isOk) *isOk = true;
    return _is_double ? static_cast<int>(_valued) : _valuei;
}

double ValueNumber::getDouble(bool* isOk) const
{
    if(isOk) *isOk = true;
    return _is_double ? _valued : static_cast<double>(_valuei);
}

bool ValueNumber::set(int val_)
{
    _valuei = val_;
    _is_double = false;
}

bool ValueNumber::set(double val_)
{
    _valued = val_;
    _is_double = true;
}

iterator_t ValueNumber::parse(iterator_t config_begin, iterator_t config_end)
{
    iterator_t number_begin = skip_trash(config_begin, config_end);
    
    iterator_t number_end = std::find_if(number_begin, config_end,
                                        std::not1(std::ptr_fun(isnumberchar)));
    
    if(number_end == number_begin) return config_begin;
    
    for(std::string::const_iterator it = _single_chars.begin(); it != _single_chars.end(); it ++){
        if(std::count(number_begin, number_end, *it) > 1) return config_begin;
    }

    std::string str_number(number_begin, number_end);

    if(std::find_first_of(number_begin, number_end,
            _only_double_chars.begin(), _only_double_chars.end()) != number_end){
        //number is double
        _is_double = true;
        _valued = strtod(str_number.c_str(), NULL);
    }else{
        _is_double = false;
        _valuei = strtol(str_number.c_str(), NULL, 0);
    }

    return number_end;
}

bool ValueNumber::isit(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    
    iterator_t not_number = std::find_if(current, config_end,
                                        std::not1(std::ptr_fun(isnumberchar)));
    
    if(not_number == current) return false;
    
    for(std::string::const_iterator it = _single_chars.begin(); it != _single_chars.end(); it ++){
        if(std::count(current, not_number, *it) > 1) return false;
    }
    
    return true;
}

bool ValueNumber::isnumberchar(value_t c)
{
    return std::find(_valid_number_chars.begin(), _valid_number_chars.end(), c)
            != _valid_number_chars.end();
}



const std::string ValueBool::_str_true = "true";
const std::string ValueBool::_str_false = "false";

ValueBool::ValueBool()
{
    _value = false;
}

ValueBool::ValueBool(bool val_)
{
    _value = val_;
}

ValueBool::~ValueBool()
{
}

bool ValueBool::getBool(bool* isOk) const
{
    if(isOk) *isOk == true;
    return _value;
}

bool ValueBool::set(bool val_)
{
    _value = val_;
}

iterator_t ValueBool::parse(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    if(_str_true.length() > std::distance(config_end, current)) return config_begin;
    if(std::equal(_str_true.begin(), _str_true.end(), current)){
        _value = true;
        std::advance(current, _str_true.length());
        return current;
    }
    if(_str_false.length() > std::distance(config_end, current)) return config_begin;
    if(std::equal(_str_false.begin(), _str_false.end(), current)){
        _value = false;
        std::advance(current, _str_false.length());
        return current;
    }
    return config_begin;
}

bool ValueBool::isit(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    if(_str_true.length() > std::distance(config_end, current)) return false;
    if(std::equal(_str_true.begin(), _str_true.end(), current)){
        return true;
    }
    if(_str_false.length() > std::distance(config_end, current)) return false;
    if(std::equal(_str_false.begin(), _str_false.end(), current)){
        return true;
    }
    return false;
}


const std::string Parameter::_parameter_sign = "=";

Parameter::Parameter(const std::string& name_)
        :NamedElement(name_)
{
    _value = NULL;
}

Parameter::~Parameter()
{
    delete _value;
}

Value& Parameter::value()
{
    
}

bool Parameter::isit(iterator_t begin, iterator_t end)
{
    return ::isit(_parameter_sign, begin, end);
}

iterator_t Parameter::parse(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    if(_parameter_sign.length() > std::distance(config_end, current)) return config_begin;
    
    if(!std::equal(_parameter_sign.begin(), _parameter_sign.end(), current)) {
        return config_begin;
    }
    
    std::advance(current, _parameter_sign.length());
    
    _value = new Value;
    
    iterator_t parse_res = _value->parse(current, config_end);
    
    if(parse_res == current) return config_begin;
    
    current = skip_trash(parse_res, config_end);
    if(Element::line_sep.length() > std::distance(config_end, current)) return config_begin;
    if(!std::equal(Element::line_sep.begin(), Element::line_sep.end(), current)) return config_begin;
    
    std::advance(current, Element::line_sep.length());
    
    return current;
}


const std::string Group::_group_begin  = "{";
const std::string Group::_group_end    = "}";
const std::string Group::_group_sign   = Group::_group_begin;

Group::Group()
        :NamedElement(std::string())
{
    _is_root = true;
    
    _def_ctor();
}

Group::Group(const std::string& name_)
        :NamedElement(name_)
{
    _is_root = false;
    
    _def_ctor();
}

void Group::_def_ctor()
{
    _groups = new Groups;
    _parameters = new Parameters;
}

Group::~Group()
{
    std::for_each(_groups->begin(), _groups->end(), utils::functors::delete_single());
    std::for_each(_parameters->begin(), _parameters->end(), utils::functors::delete_single());
    
    delete _groups;
    delete _parameters;
}

Group& Group::getGroup(const std::string& group_)
{
    
}

Parameter& Group::getParameter(const std::string& param_)
{
    
}

bool Group::isit(iterator_t begin, iterator_t end)
{
    return ::isit(_group_sign, begin, end);
}

iterator_t Group::parse(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    if(_group_begin.length() > std::distance(config_end, current)) return config_begin;
    
    if(!std::equal(_group_begin.begin(), _group_begin.end(), current)) {
        return config_begin;
    }
    
    std::advance(current, _group_begin.length());
    
    for(;;){
        current = skip_trash(config_begin, config_end);

        debug_print(current, config_end);
        
        if(_is_root == false){
            if(_group_end.length() <= std::distance(config_end, current)){
                if(std::equal(_group_end.begin(), _group_end.end(), current)){
                    std::advance(current, _group_end.length());
                    break;
                }
            }
        }
        if(current == config_end){
            break;
        }

        if(Parameter::isit(current, config_end)){
            std::string readed_name;

            current = get_name(readed_name, current, config_end);
            if(readed_name.empty()){
                    std::cout << "Invalid parameter name: " << readed_name << std::endl;
            }
            
            Parameter* param = new Parameter(readed_name);
            _parameters->push_back(param);
            
            current = param->parse(current, config_end);
            
        }else if(Group::isit(current, config_end)){

            std::string readed_name;

            current = get_name(readed_name, current, config_end);
            if(readed_name.empty()){
                    std::cout << "Invalid group name: " << readed_name << std::endl;
            }
            
            Group* grp = new Group(readed_name);
            _groups->push_back(grp);
            
            current = grp->parse(current, config_end);
            
        }else{
            std::cout << "Unknown element type" << std::endl;
            current ++;
            //return config_begin;
        }
    }
    
    return current;
}

Config::Config()
{
    _root = NULL;
}

Config::~Config()
{
    delete _root;
}

bool Config::read(std::istream& ist_)
{
    std::istreambuf_iterator<char> ist_it(ist_);
    std::istreambuf_iterator<char> eos;
    std::string config_str(ist_it, eos);
    
    iterator_t config_begin = config_str.begin();
    iterator_t config_end = config_str.end();
    
    //std::cout << config_str;
    
    return parse(config_begin, config_end) == config_end;
}

iterator_t Config::parse(iterator_t config_begin, iterator_t config_end)
{
    _root = new Group();
    
    iterator_t parse_res = _root->parse(config_begin, config_end);

    return parse_res;
}

