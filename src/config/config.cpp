#include "config.h"
#include <sstream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <ctype.h>
#include <stdlib.h>
#include <locale>
#include "utils/utils.h"

/*
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
*/

iterator_t skip_ws(iterator_t begin, iterator_t end)
{
    return std::find_if(begin, end, std::not1(std::ptr_fun(isspace)));
}

iterator_t skip_comment(const std::string& comment_begin,
                        const std::string& comment_end,
                        iterator_t begin, iterator_t end)
{
    if(comment_begin.length() > static_cast<unsigned int>(std::distance(begin, end))) return begin;
    if(std::equal(comment_begin.begin(), comment_begin.end(), begin)){
        begin = std::search(begin, end, comment_end.begin(), comment_end.end());
        if(static_cast<unsigned int>(std::distance(begin, end)) >= comment_end.length()){
            std::advance(begin, comment_end.length());
        }
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


ConfigException::ConfigException(const char* who_, const char* what_, iterator_t where_)
    :Exception(what_)
{
    _who = who_;
    _where = where_;
}

ConfigException::~ConfigException() throw()
{
}

const char* ConfigException::who() const throw()
{
    return _who.c_str();
}

iterator_t ConfigException::where() const throw()
{
    return _where;
}



const std::string Element::line_sep = ";";
const std::string Element::align_space = "    ";
const std::string Element::line_end = "\n";
const std::string Element::white_space = " ";

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

bool ValueBase::setInt(int)
{
    return false;
}

bool ValueBase::setBool(bool)
{
    return false;
}

bool ValueBase::setDouble(double)
{
    return false;
}

bool ValueBase::setConstant(const std::string&)
{
    return false;
}

bool ValueBase::setString(const std::string&)
{
    return false;
}

bool ValueBase::setVector(const std::vector<Value>&)
{
    return false;
}

iterator_t ValueBase::parse(iterator_t config_begin, iterator_t /*config_end*/) throw(ConfigException&)
{
    throw(ConfigException("ValueBase", "called parse() stub", config_begin));
}

bool ValueBase::write(std::ostream& /*ost_*/) const
{
    return false;
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


bool Value::setInt(int val_)
{
    if(_value == NULL){
        _value = new ValueNumber(val_);
    }else if(!_value->setInt(val_)){
        delete _value;
        _value = new ValueNumber(val_);
    }
    return true;
}

bool Value::setBool(bool val_)
{
    if(_value == NULL){
        _value = new ValueBool(val_);
    }else if(!_value->setBool(val_)){
        delete _value;
        _value = new ValueBool(val_);
    }
    return true;
}

bool Value::setDouble(double val_)
{
    if(_value == NULL){
        _value = new ValueNumber(val_);
    }else if(!_value->setDouble(val_)){
        delete _value;
        _value = new ValueNumber(val_);
    }
    return true;
}

bool Value::setConstant(const std::string& val_)
{
    if(_value == NULL){
        _value = new ValueConstant(val_);
    }else if(!_value->setConstant(val_)){
        delete _value;
        _value = new ValueConstant(val_);
    }
    return true;
}

bool Value::setString(const std::string& val_)
{
    if(_value == NULL){
        _value = new ValueString(val_);
    }else if(!_value->setString(val_)){
        delete _value;
        _value = new ValueString(val_);
    }
    return true;
}

bool Value::setVector(const std::vector<Value>& val_)
{
    if(_value == NULL){
        _value = new ValueVector(val_);
    }else if(!_value->setVector(val_)){
        delete _value;
        _value = new ValueVector(val_);
    }
    return true;
}

iterator_t Value::parse(iterator_t config_begin, iterator_t config_end) throw(ConfigException&)
{
    delete _value; _value = NULL;
    
    iterator_t current = skip_trash(config_begin, config_end);
    
    if(ValueNumber::isit(current, config_end)){
        _value = new ValueNumber;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current){
            throw(ConfigException("Value", "error in ValueNumber::parse()", current));
        }
        return parse_res;
    }else if(ValueString::isit(current, config_end)){
        _value = new ValueString;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current){
            throw(ConfigException("Value", "error in ValueString::parse()", current));
        }
        return parse_res;
    }else if(ValueVector::isit(current, config_end)){
        _value = new ValueVector;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current){
            throw(ConfigException("Value", "error in ValueVector::parse()", current));
        }
        return parse_res;
    }else if(ValueBool::isit(current, config_end)){
        _value = new ValueBool;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current){
            throw(ConfigException("Value", "error in ValueBool::parse()", current));
        }
        return parse_res;
    }else if(ValueConstant::isit(current, config_end)){
        _value = new ValueConstant;
        iterator_t parse_res = _value->parse(current, config_end);
        if(parse_res == current){
            throw(ConfigException("Value", "error in ValueConstant::parse()", current));
        }
        return parse_res;
    }
    throw(ConfigException("Value", "unknown value type", current));
}

bool Value::write(std::ostream& ost_) const
{
    if(_value == NULL) return false;
    return _value->write(ost_);
}


const std::string ValueNumber::_valid_number_chars = "xXeE-+.,0123456789aAbBcCdDeEfF";
const std::string ValueNumber::_only_double_chars = ".,eE";
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

bool ValueNumber::setInt(int val_)
{
    _valuei = val_;
    _is_double = false;
    return true;
}

bool ValueNumber::setDouble(double val_)
{
    _valued = val_;
    _is_double = true;
    return true;
}

iterator_t ValueNumber::parse(iterator_t config_begin, iterator_t config_end) throw(ConfigException&)
{
    _is_double = false;
    _valuei = 0;
    
    iterator_t number_begin = skip_trash(config_begin, config_end);
    
    iterator_t number_end = std::find_if(number_begin, config_end,
                                        std::not1(std::ptr_fun(isnumberchar)));
    
    if(number_end == number_begin){
        throw(ConfigException("ValueNumber", "length of value is equal to zero", number_begin));
    }
    
    for(std::string::const_iterator it = _single_chars.begin(); it != _single_chars.end(); ++ it){
        if(std::count(number_begin, number_end, *it) > 1){
            throw(ConfigException("ValueNumber", "bad number", number_begin));
        }
    }

    std::string str_number(number_begin, number_end);
    
    if(std::has_facet<std::numpunct<char> >(std::locale())){
        try{
            char num_dot = std::use_facet<std::numpunct<char> >(std::locale()).decimal_point();
            std::replace(str_number.begin(), str_number.end(),
                    (num_dot == '.') ? ',' : '.', num_dot);
        }catch(...){}
    }

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

bool ValueNumber::write(std::ostream& ost_) const
{
    if(_is_double) ost_ << _valued;
    else ost_ << _valuei;
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

bool ValueBool::setBool(bool val_)
{
    _value = val_;
    return true;
}

iterator_t ValueBool::parse(iterator_t config_begin, iterator_t config_end) throw(ConfigException&)
{
    _value = false;
    
    iterator_t current = skip_trash(config_begin, config_end);
    if(_str_true.length() > static_cast<unsigned int>(std::distance(current, config_end))){
        throw(ConfigException("ValueBool", "bad value length", current));
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
    throw(ConfigException("ValueBool", "string \"true\" or \"false\" not found", current));
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

bool ValueBool::write(std::ostream& ost_) const
{
    if(_value) ost_ << _str_true;
    else ost_ << _str_false;
    return true;
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

iterator_t ValueConstant::parse(iterator_t config_begin, iterator_t config_end) throw(ConfigException&)
{
    _value.clear();
    
    iterator_t current = skip_trash(config_begin, config_end);
    
    if(current == config_end){
        throw(ConfigException("ValueConstant", "length of value is equal to zero", current));
    }
    
    iterator_t end_name = get_name(_value, current, config_end);
    
    if(end_name == current){
        throw(ConfigException("ValueConstant", "bad constant name", current));
    }
    
    return end_name;
}

bool ValueConstant::isit(iterator_t config_begin, iterator_t config_end)
{
    iterator_t current = skip_trash(config_begin, config_end);
    
    if(current == config_end) return false;
    
    return isnamechar(*current, true);
}

bool ValueConstant::write(std::ostream& ost_) const
{
    if(_value.empty()) return false;
    ost_ << _value;
    return true;
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

bool ValueString::setString(const std::string& val_)
{
    _value = val_;
    return true;
}

iterator_t ValueString::parse(iterator_t config_begin, iterator_t config_end) throw(ConfigException&)
{
    _value.clear();
    
    iterator_t current = skip_trash(config_begin, config_end);
    
    if((_string_begin_end.length() << 1) > static_cast<unsigned int>(std::distance(current, config_end))){
        throw(ConfigException("ValueString", "bad length", current));
    }
    
    if(!std::equal(_string_begin_end.begin(), _string_begin_end.end(), current)){
        throw(ConfigException("ValueString", "string begin symbol not found", current));
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
                    _value.push_back(*current);
                    break;
            }
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
                    //std::cout << "warning: unknown escape-character \"\\" << *current << "\"" << std::endl;
                    _value.push_back(*current);
                    break;
            }
            after_bslash = false;
        }
    }
    
    throw(ConfigException("ValueString", "string end symbol not found", current));
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

bool ValueString::write(std::ostream& ost_) const
{
    //std::ostreambuf_iterator<char> out_it(ost_);
    ost_ << _string_begin_end;
    for(iterator_t it = _value.begin(); it != _value.end(); ++it){
        switch(*it){
            case '\n':
                ost_ << "\\n";
                break;
            case '\r':
                ost_ << "\\r";
                break;
            case '\v':
                ost_ << "\\v";
                break;
            case '\t':
                ost_ << "\\t";
                break;
            case '"':
                ost_ << "\\\"";
                break;
            case '\\':
                ost_ << "\\\\";
                break;
            default:
                ost_ << *it;
        }
    }
    ost_ << _string_begin_end;
    return true;
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

bool ValueVector::setVector(const std::vector<Value>& val_)
{
    delete _value;
    _value = new std::vector<Value>(val_.begin(), val_.end());
    return true;
}

iterator_t ValueVector::parse(iterator_t config_begin, iterator_t config_end) throw(ConfigException&)
{
    delete _value; _value = NULL;
    
    iterator_t current = skip_trash(config_begin, config_end);
    
    if((_vector_begin.length() + _vector_end.length()) >
            static_cast<unsigned int>(std::distance(current, config_end))){
        throw(ConfigException("ValueVector", "bad length", current));
    }
    
    if(!std::equal(_vector_begin.begin(), _vector_begin.end(), current)){
        throw(ConfigException("ValueVector", "vector begin symbol not found", current));
    }
    
    std::advance(current, _vector_begin.length());
    
    _value = new std::vector<Value>;
    
    current = skip_trash(current, config_end);
    
    if(_vector_end.length() > static_cast<unsigned int>(std::distance(current, config_end))){
        throw(ConfigException("ValueVector", "bad length for vector end symbol", current));
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
            throw(ConfigException("ValueVector", "Value::parse() error", current));
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
            throw(ConfigException("ValueVector", "bad length for separator", current));
        }
        
        if(!std::equal(_vector_sep.begin(), _vector_sep.end(), current)){
            throw(ConfigException("ValueVector", "bad separator in vector", current));
        }
        
        std::advance(current, _vector_sep.length());
    }
    
    throw(ConfigException("ValueVector", "vector end symbol not found", current));
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

bool ValueVector::write(std::ostream& ost_) const
{
    if(_value == NULL) return false;
    
    ost_ << _vector_begin;
    
    for(std::vector<Value>::iterator it = _value->begin(); it != _value->end(); ++it){
        (*it).write(ost_);
        if(std::distance(it, _value->end()) > 1) ost_ << _vector_sep << Element::white_space;
    }
    
    ost_ << _vector_end;
    
    return true;
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

Value* Parameter::getValue()
{
    return _value;
}

void Parameter::setValue(const Value* value_)
{
    delete _value;
    _value = value_->clone();
}

bool Parameter::isit(iterator_t begin, iterator_t end)
{
    return ::isit(_parameter_sign, begin, end);
}

iterator_t Parameter::parse(iterator_t config_begin, iterator_t config_end) throw(ConfigException&)
{
    delete _value; _value = NULL;
    
    iterator_t current = skip_trash(config_begin, config_end);
    if(_parameter_sign.length() > static_cast<unsigned int>(std::distance(current, config_end))){
        throw(ConfigException("Parameter", "bad length", current));
    }
    
    if(!std::equal(_parameter_sign.begin(), _parameter_sign.end(), current)) {
        throw(ConfigException("Parameter", "bad signature", current));
    }
    
    std::advance(current, _parameter_sign.length());
    
    _value = new Value;
    
    iterator_t parse_res = _value->parse(current, config_end);
    
    if(parse_res == current){
        throw(ConfigException("Parameter", "Value::parse() error", current));
    }
    
    current = skip_trash(parse_res, config_end);
    if(Element::line_sep.length() > static_cast<unsigned int>(std::distance(current, config_end))){
        throw(ConfigException("Parameter", "bad length for parameter end", current));
    }
    if(!std::equal(Element::line_sep.begin(), Element::line_sep.end(), current)){
        throw(ConfigException("Parameter", "parameter end symbol not found", current));
    }
    
    std::advance(current, Element::line_sep.length());
    
    return current;
}

bool Parameter::write(std::ostream& ost_) const
{
    if(_value == NULL) return true;//false;
    
    ost_ << _name << Element::white_space << _parameter_sign << Element::white_space;
    
    if(!_value->write(ost_)) return false;
    
    ost_ << Element::line_sep;
    
    return true;
}

const std::string Group::_group_begin  = "{";
const std::string Group::_group_end    = "}";
const std::string Group::_group_sign   = Group::_group_begin;

const std::string Group::_group_sep = ".";

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
    _clear();
    
    delete _groups;
    delete _parameters;
}

void Group::_clear()
{
    std::for_each(_groups->begin(), _groups->end(), functors::delete_single());
    std::for_each(_parameters->begin(), _parameters->end(), functors::delete_single());
    
    _groups->clear();
    _parameters->clear();
}

Group* Group::addGroup(const std::string& name)
{
    Group* res = new Group(name);
    _groups->push_back(res);
    
    return res;
}

Parameter* Group::addParameter(const std::string& name)
{
    Parameter* res = new Parameter(name);
    _parameters->push_back(res);
    
    return res;
}

Group* Group::getGroup(const std::string& group_)
{
    for(Groups::iterator it = _groups->begin(); it != _groups->end(); ++it){
        if((*it)->name() == group_) return *it;
    }
    return NULL;
}

Parameter* Group::getParameter(const std::string& param_)
{
    for(Parameters::iterator it = _parameters->begin(); it != _parameters->end(); ++it){
        if((*it)->name() == param_) return *it;
    }
    return NULL;
}

bool Group::isit(iterator_t begin, iterator_t end)
{
    return ::isit(_group_sign, begin, end);
}

iterator_t Group::parse(iterator_t config_begin, iterator_t config_end) throw(ConfigException&)
{
    _clear();
    
    iterator_t current = config_begin;
    
    if(_is_root == false){
        
        current = skip_trash(current, config_end);
        
        if(_group_begin.length() > static_cast<unsigned int>(std::distance(current, config_end))){
            throw(ConfigException("Group", "bad length", current));
        }
        
        if(!std::equal(_group_begin.begin(), _group_begin.end(), current)) {
            throw(ConfigException("Group", "group begin symbol not found", current));
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
                throw(ConfigException("Group", "invalid parameter name", current));
            }
            
            Parameter* param = getParameter(readed_name);
            if(param == NULL) param = addParameter(readed_name);
            //else debug_msg("Group::Warning replacing parameter");
            //_parameters->push_back(param);
            
            iterator_t parse_res = param->parse(current, config_end);
            
            if(parse_res == current){
                throw(ConfigException("Group", "Parameter::parse() error", current));
            }
            
            current = parse_res;
            
        }else if(Group::isit(current, config_end)){

            std::string readed_name;

            current = get_name(readed_name, current, config_end);
            if(readed_name.empty()){
                throw(ConfigException("Group", "invalid group name", current));
            }
            
            Group* grp = getGroup(readed_name);
            if(grp == NULL) grp = addGroup(readed_name);
            //else debug_msg("Group::Warning replacing group");
            //_groups->push_back(grp);
            
            iterator_t parse_res = grp->parse(current, config_end);
            
            if(parse_res == current){
                throw(ConfigException("Group", "Group::parse() error", current));
            }
            
            current = parse_res;
            
        }else{
            throw(ConfigException("Group", "bad character or unknown element type", current));
        }
    }
    
    return current;
}

bool Group::write(std::ostream& ost_, size_t lvl) const
{
    size_t cur_lvl = lvl;
    
    //if this is not root node
    if(_is_root == false){
        //inc current lvl
        cur_lvl ++;
        //write align spaces
        for(size_t i = 0; i < lvl; i++) ost_ << Element::align_space;
        //write group name and begin symbol
        ost_ << _name << _group_begin << Element::line_end;
    }
    
    //parameters
    for(Parameters::iterator it = _parameters->begin(); it != _parameters->end(); ++it){
        //write align spaces
        for(size_t i = 0; i < cur_lvl; i++) ost_ << Element::align_space;
        //write parameter
        if(!(*it)->write(ost_)) return false;
        //write endl
        ost_ << Element::line_end;
    }
    
    if(!_parameters->empty() && !_groups->empty()){
        //write endl (parameters - groups separator)
        ost_ << Element::line_end;
    }
    
    //groups
    for(Groups::iterator it = _groups->begin(); it != _groups->end(); ++it){
        //write group
        if(!(*it)->write(ost_, cur_lvl)) return false;
        //wrute endl
        ost_ << Element::line_end;
        //write endl between neighboring groups
        if(std::distance(it, _groups->end()) > 1){
            ost_ << Element::line_end;
        }
    }
    
    //if not root
    if(_is_root == false){
        //write align
        for(size_t i = 0; i < lvl; i++) ost_ << Element::align_space;
        //write group end symbol
        ost_ << _group_end;// << Element::line_end;
    }
    
    return true;
}

Value* Group::getValue(const std::string& parameter_)
{
    if(parameter_.empty()) return NULL;
    
    std::string group_name;
    
    iterator_t end_name = get_name(group_name, parameter_.begin(), parameter_.end());
    
    if(end_name == parameter_.end()){
        Parameter* parameter = getParameter(parameter_);
        if(parameter != NULL){
            return parameter->getValue();
        }
        return NULL;
    }
    
    if(_group_sep.length() > static_cast<unsigned int>(std::distance(end_name, parameter_.end()))){
        //debug_msg("Group::getValue::Error bad length");
        return NULL;
    }
    
    if(!std::equal(_group_sep.begin(), _group_sep.end(), end_name)){
        //debug_msg("Group::getValue::Error invalid separator");
        return NULL;
    }
    
    
    Group* group = getGroup(group_name);
    
    if(group == NULL){
        //debug_msg("Group::getValue::Error group not found");
        return NULL;
    }
    
    std::advance(end_name, _group_sep.length());
    
    std::string parameter_name(end_name, parameter_.end());
    return group->getValue(parameter_name);
}

bool Group::setValue(const std::string& parameter_, const Value* value_)
{
    if(parameter_.empty()) return false;
    
    std::string group_name;
    
    iterator_t end_name = get_name(group_name, parameter_.begin(), parameter_.end());
    
    if(end_name == parameter_.end()){
        Parameter* parameter = getParameter(parameter_);
        if(parameter == NULL) parameter = addParameter(group_name);
        parameter->setValue(value_);
        return true;
    }
    
    if(_group_sep.length() > static_cast<unsigned int>(std::distance(end_name, parameter_.end()))){
        //debug_msg("Group::setValue::Error bad length");
        return false;
    }
    
    if(!std::equal(_group_sep.begin(), _group_sep.end(), end_name)){
        //debug_msg("Group::setValue::Error invalid separator");
        return false;
    }
    
    
    Group* group = getGroup(group_name);
    if(group == NULL) group = addGroup(group_name);
    
    std::advance(end_name, _group_sep.length());
    
    std::string parameter_name(end_name, parameter_.end());
    
    group->setValue(parameter_name, value_);
    
    return true;
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
    
    /*if(parse(config_begin, config_end) != config_end){
        clear();
        return false;
    }*/
    try
    {
        if(parse(config_begin, config_end) == config_end){
            return true;
        }
    }
    catch (ConfigException& ce)
    {
        //calc lines count
        int line = std::count(config_begin, ce.where(), Element::line_end.c_str()[0]);
        //find last line
        iterator_t last_line = std::find_end(config_begin, ce.where(),
                            Element::line_end.begin(), Element::line_end.end());
        if(last_line == ce.where()){
            last_line = config_begin;
        }
        //calc position
        int pos = std::distance(last_line, ce.where());
        
        std::cout << "line " << line + 1
                  << " position " << pos +1
                  << ": " <<  ce.who() << ": " << ce.what() << std::endl;
    }
    
    clear();
    
    return false;
}

void Config::clear()
{
    delete _root;
    _root = NULL;
}

bool Config::write(std::ostream& ost_) const
{
    if(_root != NULL){
        return _root->write(ost_);
    }
    return false;
}

iterator_t Config::parse(iterator_t config_begin, iterator_t config_end)
{
    delete _root;
    _root = new Group();
    
    iterator_t parse_res = _root->parse(config_begin, config_end);

    return parse_res;
}

int Config::getInt(const std::string& parameter_, bool* isOk) const
{
    Value* value = getValue(parameter_);
    if(value){
        return value->getInt(isOk);
    }
    if(isOk) *isOk = false;
    return int();
}

bool Config::getBool(const std::string& parameter_, bool* isOk) const
{
    Value* value = getValue(parameter_);
    if(value){
        return value->getBool(isOk);
    }
    if(isOk) *isOk = false;
    return bool();
}

double Config::getDouble(const std::string& parameter_, bool* isOk) const
{
    Value* value = getValue(parameter_);
    if(value){
        return value->getDouble(isOk);
    }
    if(isOk) *isOk = false;
    return double();
}

std::string Config::getConstant(const std::string& parameter_, bool* isOk) const
{
    Value* value = getValue(parameter_);
    if(value){
        return value->getConstant(isOk);
    }
    if(isOk) *isOk = false;
    return std::string();
}

std::string Config::getString(const std::string& parameter_, bool* isOk) const
{
    Value* value = getValue(parameter_);
    if(value){
        return value->getString(isOk);
    }
    if(isOk) *isOk = false;
    return std::string();
}

std::vector<Value> Config::getVector(const std::string& parameter_, bool* isOk) const
{
    Value* value = getValue(parameter_);
    if(value){
        return value->getVector(isOk);
    }
    if(isOk) *isOk = false;
    return std::vector<Value>();
}


bool Config::setInt(const std::string& parameter_, int value_)
{
    Value* pvalue = getValue(parameter_);
    if(pvalue){
        return pvalue->setInt(value_);
    }

    Value value;
    value.setInt(value_);

    return setValue(parameter_, value);;
}

bool Config::setBool(const std::string& parameter_, bool value_)
{
    Value* pvalue = getValue(parameter_);
    if(pvalue){
        return pvalue->setBool(value_);
    }
    
    Value value;
    value.setBool(value_);

    return setValue(parameter_, value);
}

bool Config::setDouble(const std::string& parameter_, double value_)
{
    Value* pvalue = getValue(parameter_);
    if(pvalue){
        return pvalue->setDouble(value_);
    }
    
    Value value;
    value.setDouble(value_);
    
    return setValue(parameter_, value);
}

bool Config::setConstant(const std::string& parameter_, const std::string& value_)
{
    Value* pvalue = getValue(parameter_);
    if(pvalue){
        return pvalue->setConstant(value_);
    }
    
    Value value;
    value.setConstant(value_);
    
    return setValue(parameter_, value);
}

bool Config::setString(const std::string& parameter_, const std::string& value_)
{
    Value* pvalue = getValue(parameter_);
    if(pvalue){
        return pvalue->setString(value_);
    }
    
    Value value;
    value.setString(value_);
    
    return setValue(parameter_, value);
}

bool Config::setVector(const std::string& parameter_, const std::vector<Value>& value_)
{
    Value* pvalue = getValue(parameter_);
    if(pvalue){
        return pvalue->setVector(value_);
    }
    
    Value value;
    value.setVector(value_);
    
    return setValue(parameter_, value);
}

Value* Config::getValue(const std::string& parameter_) const
{
    if(_root != NULL){
        return _root->getValue(parameter_);
    }
    return NULL;
}

bool Config::setValue(const std::string& parameter_, const Value& value_)
{
    if(_root == NULL) _root = new Group;
    return _root->setValue(parameter_, &value_);
}


std::istream& operator>>(std::istream& ist, Config& config)
{
    config.read(ist);
    return ist;
}

std::ostream& operator<<(std::ostream& ost, const Config& config)
{
    config.write(ost);
    return ost;
}
