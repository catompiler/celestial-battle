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

void debug_msg(const char* msg)
{
    std::cout << msg << std::endl;
}


iterator_t skip_ws(iterator_t begin, iterator_t end)
{
    return std::find_if(begin, end, std::not1(std::ptr_fun(isspace)));
}

iterator_t skip_comment(const std::string& comment_begin,
                        const std::string comment_end,
                        iterator_t begin, iterator_t end)
{
    if(comment_begin.length() > static_cast<unsigned int>(std::distance(begin, end))) return begin;
    if(std::equal(comment_begin.begin(), comment_begin.end(), begin)){
        begin = std::search(begin, end, comment_end.begin(), comment_end.end());
        if(static_cast<unsigned int>(std::distance(begin, end)) >= comment_end.length()) std::advance(begin, comment_end.length());
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
    if(sign.length() > static_cast<unsigned int>(std::distance(begin, end))) return false;
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

ValueBase::ValueBase(const ValueBase&)
{
}

ValueBase::~ValueBase()
{
}

ValueBase* ValueBase::clone() const
{
    return new ValueBase(*this);
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

std::string ValueBase::getConstant(bool* isOk) const
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

bool ValueBase::setConstant(const std::string&)
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
    debug_msg("ValueBase::parse()");
    return config_begin;
}


Value::Value()
{
    _value = NULL;
}

Value::Value(const Value& value_)
{
    if(value_._value != NULL) _value = value_._value->clone();
    else _value = NULL;
}

Value::~Value()
{
    delete _value;
}

Value* Value::clone() const
{
    return new Value(*this);
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

std::string Value::getConstant(bool* isOk) const
{
    if(_value == NULL) return ValueBase::getConstant(isOk);
    return _value->getConstant(isOk);
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

bool Value::setConstant(const std::string& val_)
{
    if(_value == NULL){
        return ValueBase::setConstant(val_);
    }else if(!_value->setConstant(val_)){
        delete _value;
        _value = new ValueConstant(val_);
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
        debug_msg("Value::Info parsing number");
        _value = new ValueNumber;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current){
            debug_msg("Value::Error in ValueNumber::parse()");
            return config_begin;
        }
        return parse_res;
    }else if(ValueString::isit(current, config_end)){
        debug_msg("Value::Info parsing string");
        _value = new ValueString;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current){
            debug_msg("Value::Error in ValueString::parse()");
            return config_begin;
        }
        return parse_res;
    }else if(ValueVector::isit(current, config_end)){
        debug_msg("Value::Info parsing vector");
        _value = new ValueVector;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current){
            debug_msg("Value::Error in ValueVector::parse()");
            return config_begin;
        }
        return parse_res;
    }else if(ValueBool::isit(current, config_end)){
        debug_msg("Value::Info parsing boolean");
        _value = new ValueBool;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current){
            debug_msg("Value::Error in ValueBool::parse()");
            return config_begin;
        }
        return parse_res;
    }else if(ValueConstant::isit(current, config_end)){
        debug_msg("Value::Info parsing constant");
        _value = new ValueConstant;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current){
            debug_msg("Value::Error in ValueConstant::parse()");
            return config_begin;
        }
        return parse_res;
    }
    debug_msg("Value::Error Unknown value type");
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

ValueNumber::ValueNumber(const ValueNumber& value_)
{
    _is_double = value_._is_double;
    if(value_._is_double) _valued = value_._valued;
    else _valuei = value_._valuei;
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

ValueNumber* ValueNumber::clone() const
{
    return new ValueNumber(*this);
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
    return true;
}

bool ValueNumber::set(double val_)
{
    _valued = val_;
    _is_double = true;
    return true;
}

iterator_t ValueNumber::parse(iterator_t config_begin, iterator_t config_end)
{
    iterator_t number_begin = skip_trash(config_begin, config_end);
    
    iterator_t number_end = std::find_if(number_begin, config_end,
                                        std::not1(std::ptr_fun(isnumberchar)));
    
    if(number_end == number_begin){
        debug_msg("ValueNumber::Error length is equal to zero");
        return config_begin;
    }
    
    for(std::string::const_iterator it = _single_chars.begin(); it != _single_chars.end(); it ++){
        if(std::count(number_begin, number_end, *it) > 1){
            debug_msg("ValueNumber::Error bad number");
            return config_begin;
        }
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
    
    /*for(std::string::const_iterator it = _single_chars.begin(); it != _single_chars.end(); it ++){
        if(std::count(current, not_number, *it) > 1) return false;
    }*/
    
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

ValueBool::ValueBool(const ValueBool& value_)
{
    _value = value_._value;
}

ValueBool::ValueBool(bool val_)
{
    _value = val_;
}

ValueBool::~ValueBool()
{
}

ValueBool* ValueBool::clone() const
{
    return new ValueBool(*this);
}

bool ValueBool::getBool(bool* isOk) const
{
    if(isOk) *isOk = true;
    return _value;
}

bool ValueBool::set(bool val_)
{
    _value = val_;
    return true;
}

iterator_t ValueBool::parse(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    if(_str_true.length() > static_cast<unsigned int>(std::distance(current, config_end))){
        debug_msg("ValueBool::Error bad length");
        return config_begin;
    }
    if(std::equal(_str_true.begin(), _str_true.end(), current)){
        _value = true;
        std::advance(current, _str_true.length());
        return current;
    }
    if(_str_false.length() > static_cast<unsigned int>(std::distance(current, config_end))) return config_begin;
    if(std::equal(_str_false.begin(), _str_false.end(), current)){
        _value = false;
        std::advance(current, _str_false.length());
        return current;
    }
    debug_msg("ValueBool::Error string \"true\" or \"false\" not found");
    return config_begin;
}

bool ValueBool::isit(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    if(_str_true.length() > static_cast<unsigned int>(std::distance(current, config_end))) return false;
    if(std::equal(_str_true.begin(), _str_true.end(), current)){
        return true;
    }
    if(_str_false.length() > static_cast<unsigned int>(std::distance(current, config_end))) return false;
    if(std::equal(_str_false.begin(), _str_false.end(), current)){
        return true;
    }
    return false;
}



ValueConstant::ValueConstant()
{
    _value = "";
}

ValueConstant::ValueConstant(const ValueConstant& value_)
{
    _value = value_._value;
}

ValueConstant::ValueConstant(const std::string& val_)
{
    _value = val_;
}

ValueConstant::~ValueConstant()
{
}

ValueConstant* ValueConstant::clone() const
{
    return new ValueConstant(*this);
}

std::string ValueConstant::getConstant(bool* isOk) const
{
    if(isOk) *isOk = true;
    return _value;
}

bool ValueConstant::setConstant(const std::string& val_)
{
    _value = val_;
    return true;
}

iterator_t ValueConstant::parse(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    
    if(current == config_end){
        debug_msg("ValueConstant::Error length is equal to zero");
        return config_begin;
    }
    
    iterator_t end_name = get_name(_value, current, config_end);
    
    if(end_name == current){
        debug_msg("ValueConstant::Error bad constant name");
        return config_begin;
    }
    
    return end_name;
}

bool ValueConstant::isit(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    
    if(current == config_end) return false;
    
    return isnamechar(*current, true);
}



const std::string ValueString::_string_begin_end = "\"";

ValueString::ValueString()
{
    _value = "";
}

ValueString::ValueString(const ValueString& value_)
{
    _value = value_._value;
}

ValueString::ValueString(const std::string& val_)
{
    _value = val_;
}

ValueString::~ValueString()
{
}

ValueString* ValueString::clone() const
{
    return new ValueString(*this);
}

std::string ValueString::getString(bool* isOk) const
{
    if(isOk) *isOk = true;
    return _value;
}

bool ValueString::set(const std::string& val_)
{
    _value = val_;
    return true;
}

iterator_t ValueString::parse(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    
    if(_string_begin_end.length() > static_cast<unsigned int>(std::distance(current, config_end))){
        debug_msg("ValueString::Error bad length");
        return config_begin;
    }
    
    if(!std::equal(_string_begin_end.begin(), _string_begin_end.end(), current)){
        debug_msg("ValueString::Error string begin symbol not found");
        return config_begin;
    }
    
    std::advance(current, _string_begin_end.length());
    
    bool after_bslash = false;
    for(; current != config_end; ++current){
        if(after_bslash == false){
            switch(*current){
                case '\\':
                    after_bslash = true;
                    break;
                case '"':
                    return ++current;
                default:
                    break;
            }
            _value.push_back(*current);
        }else{
            switch(*current){
                case 'n':
                    _value.push_back('\n');
                    break;
                case 'r':
                    _value.push_back('\r');
                    break;
                case 'v':
                    _value.push_back('\v');
                    break;
                case 't':
                    _value.push_back('\t');
                    break;
                /*case '':
                    _value.push_back('\');
                    break;*/
                case '"':
                    _value.push_back('"');
                    break;
                case '\\':
                    _value.push_back('\\');
                    break;
                default:
                    std::cout << "warning: unknown escape-character \"\\" << *current << "\"" << std::endl;
                    _value.push_back(*current);
                    break;
            }
            after_bslash = false;
        }
    }
    debug_msg("ValueString::Error string end symbol not found");
    return config_begin;
}

bool ValueString::isit(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    
    if(_string_begin_end.length() > static_cast<unsigned int>(std::distance(current, config_end))) return false;
    
    if(std::equal(_string_begin_end.begin(), _string_begin_end.end(), current)){
        return true;
    }
    
    return false;
}


const std::string ValueVector::_vector_begin = "(";
const std::string ValueVector::_vector_end   = ")";
const std::string ValueVector::_vector_sep   = ",";

ValueVector::ValueVector()
{
    _value = NULL;
}

ValueVector::ValueVector(const ValueVector& value_)
{
    if(value_._value != NULL){
        _value = new std::vector<Value>(value_._value->begin(), value_._value->end());
    }
}

ValueVector::ValueVector(const std::vector<Value>& val_)
{
    delete _value;
    _value = new std::vector<Value>(val_.begin(), val_.end());
}

ValueVector::~ValueVector()
{
    delete _value;
}

ValueVector* ValueVector::clone() const
{
    return new ValueVector(*this);
}

std::vector<Value> ValueVector::getVector(bool* isOk) const
{
    if(_value == NULL) return ValueBase::getVector(isOk);
    if(isOk) *isOk = true;
    return *_value;
}

bool ValueVector::set(const std::vector<Value>& val_)
{
    delete _value;
    _value = new std::vector<Value>(val_.begin(), val_.end());
    return true;
}

iterator_t ValueVector::parse(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    
    if(_vector_begin.length() > static_cast<unsigned int>(std::distance(current, config_end))){
        debug_msg("ValueVector::Error bad length");
        return config_begin;
    }
    
    if(!std::equal(_vector_begin.begin(), _vector_begin.end(), current)){
        debug_msg("ValueVector::Error vector begin symbol not found");
        return config_begin;
    }
    
    std::advance(current, _vector_begin.length());
    
    _value = new std::vector<Value>;
    
    current = skip_trash(current, config_end);
    
    if(_vector_end.length() > static_cast<unsigned int>(std::distance(current, config_end))){
        debug_msg("ValueVector::Error bad length for vector end symbol");
        return config_begin;
    }
    
    //if end of vector
    if(std::equal(_vector_end.begin(), _vector_end.end(), current)){
        std::advance(current, _vector_end.length());
        return current;
    }
    
    for(; current != config_end; /*++current*/){
        
        current = skip_trash(current, config_end);
        
        Value value;
        
        iterator_t parse_res = value.parse(current, config_end);
        if(parse_res == current){
            debug_msg("ValueVector::Error Value::parse() error");
            return config_begin;
        }
        
        _value->push_back(value);
        
        current = skip_trash(parse_res, config_end);
        
        if(_vector_end.length() <= static_cast<unsigned int>(std::distance(current, config_end))){
            //if end of vector
            if(std::equal(_vector_end.begin(), _vector_end.end(), current)){
                std::advance(current, _vector_end.length());
                return current;
            }
        }
        
        if(_vector_sep.length() > static_cast<unsigned int>(std::distance(current, config_end))){
            debug_msg("ValueVector::Error bad length for separator");
            return config_begin;
        }
        
        if(!std::equal(_vector_sep.begin(), _vector_sep.end(), current)){
            debug_msg("ValueVector::Error bad separator in vector");
            return config_begin;
        }
        
        std::advance(current, _vector_sep.length());
    }
    
    //!!
    return config_begin;
}

bool ValueVector::isit(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    
    if(_vector_begin.length() > static_cast<unsigned int>(std::distance(current, config_end))) return false;
    
    if(std::equal(_vector_begin.begin(), _vector_begin.end(), current)){
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
    if(_value == NULL) _value = new Value;
    return *_value;
}

bool Parameter::isit(iterator_t begin, iterator_t end)
{
    return ::isit(_parameter_sign, begin, end);
}

iterator_t Parameter::parse(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    if(_parameter_sign.length() > static_cast<unsigned int>(std::distance(current, config_end))){
        debug_msg("Parameter::Error bad length");
        return config_begin;
    }
    
    if(!std::equal(_parameter_sign.begin(), _parameter_sign.end(), current)) {
        debug_msg("Parameter::Error bad signature");
        return config_begin;
    }
    
    std::advance(current, _parameter_sign.length());
    
    _value = new Value;
    
    iterator_t parse_res = _value->parse(current, config_end);
    
    if(parse_res == current){
        debug_msg("Parameter::Error Value::parse() error");
        return config_begin;
    }
    
    current = skip_trash(parse_res, config_end);
    if(Element::line_sep.length() > static_cast<unsigned int>(std::distance(current, config_end))){
        debug_msg("Parameter::Error error length for parameter end");
        return config_begin;
    }
    if(!std::equal(Element::line_sep.begin(), Element::line_sep.end(), current)){
        debug_msg("Parameter::Error parameter end symbol not found");
        return config_begin;
    }
    
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
    iterator_t current = config_begin;
    
    if(_is_root == false){
        
        current = skip_trash(current, config_end);
        
        if(_group_begin.length() > static_cast<unsigned int>(std::distance(current, config_end))){
            debug_msg("Group::Error bad length");
            return config_begin;
        }
        
        if(!std::equal(_group_begin.begin(), _group_begin.end(), current)) {
            debug_msg("Group::Error group begin symbol not found");
            return config_begin;
        }
        
        std::advance(current, _group_begin.length());
    }
    
    for(;;){
        current = skip_trash(current, config_end);

        //debug_print(current, config_end);
        
        if(_is_root == false){
            if(_group_end.length() <= static_cast<unsigned int>(std::distance(current, config_end))){
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
                debug_msg("Group::Error invalid parameter name");
                return config_begin;
            }
            
            Parameter* param = new Parameter(readed_name);
            _parameters->push_back(param);
            
            iterator_t parse_res = param->parse(current, config_end);
            
            if(parse_res == current){
                debug_msg("Group::Error Parameter::parse() error");
                return config_begin;
            }
            
            current = parse_res;
            
        }else if(Group::isit(current, config_end)){

            std::string readed_name;

            current = get_name(readed_name, current, config_end);
            if(readed_name.empty()){
                debug_msg("Group::Error invalid group name");
                return config_begin;
            }
            
            Group* grp = new Group(readed_name);
            _groups->push_back(grp);
            
            iterator_t parse_res = grp->parse(current, config_end);
            
            if(parse_res == current){
                debug_msg("Group::Error Group::parse() error");
                return config_begin;
            }
            
            current = parse_res;
            
        }else{
            debug_msg("Group::Error unknown element type");
            //current ++;
            return config_begin;
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

