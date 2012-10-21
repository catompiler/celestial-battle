#include "config.h"
//#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string>
#include "glmath/glmath.h"
#include "utils/utils.h"
#include "tokenizer/tokenizer.h"
#include "tokenizer/tokens.h"
#include "tokenizer/tokenparsers.h"
#include "tokenizer/tokenssequence.h"
#include "configexception.h"


#define TOKEN_SPACES_GID 1
#define TOKEN_VALUES_GID 6
#define TOKEN_OPERATORS_GID 7
#define TOKEN_BLOCKS_GID 8

//ws
#define TOKEN_C_COMMENT_ID 10
#define TOKEN_CPP_COMMENT_ID 11
//#define TOKEN_NEWLINE_ID 12
//#define TOKEN_SPACE_ID 13
//#define TOKEN_TAB_ID 14
#define TOKEN_DELIMITERS_ID 15
//values
#define TOKEN_NAME_ID 500
#define TOKEN_NUMBER_ID 501
#define TOKEN_STRING_ID 502
//operators
#define TOKEN_OPERATOR_ASSIGMENT_ID 600
#define TOKEN_OPERATOR_PLUS_ID 601
#define TOKEN_OPERATOR_MINUS_ID 602
#define TOKEN_OPERATOR_ENUMERATION_ID 603
//blocks
#define TOKEN_EXPRESSION_BEGIN_ID 700
#define TOKEN_EXPRESSION_END_ID 701
#define TOKEN_END_ID 704
#define TOKEN_BLOCK_BEGIN_ID 705
#define TOKEN_BLOCK_END_ID 706



Config::Element::Element()
{
}

Config::Element::Element(const std::string& name_)
{
    _name = name_;
}

Config::Element::~Element()
{
}

const std::string& Config::Element::name() const
{
    return _name;
}

void Config::Element::setName(const std::string& name_)
{
    _name = name_;
}

std::ostream& Config::Element::writeDepth(std::ostream& ost_, const std::string& indent_, size_t depth_) const
{
    for(size_t i = 0; i < depth_; i ++) ost_ << indent_;
    return ost_;
}


Config::Parameter::Parameter()
    :Element()
{
}

Config::Parameter::Parameter(const std::string& name_)
    :Element(name_)
{
}

Config::Parameter::~Parameter()
{
}

std::ostream& Config::Parameter::write(std::ostream& ost_, const std::string& indent_, size_t depth_) const
{
    writeDepth(ost_, indent_, depth_);
    
    ost_ << _name << " = ";
    
    try{
        switch(_value.typeIndex()){
            case tl::index_of<ValueTypes, int>::value:{
                ost_ << _value.get<int>();
            }break;
            case tl::index_of<ValueTypes, float>::value:{
                ost_ << _value.get<float>();
            }break;
            case tl::index_of<ValueTypes, std::string>::value:{
                ost_ << "\"" << CStringToken::escapeString(_value.get<std::string>()) << "\"";
            }break;
            case tl::index_of<ValueTypes, vec2_t>::value:{
                const vec2_t& v = _value.get<vec2_t>();
                ost_ << "vec2(";
                for(size_t i = 0; i < vec2_t::components_count; i ++){
                    ost_ << v[i];
                    if(i < vec2_t::components_count - 1) ost_ << ", ";
                }
                ost_ << ")";
            }break;
            case tl::index_of<ValueTypes, vec3_t>::value:{
                const vec3_t& v = _value.get<vec3_t>();
                ost_ << "vec3(";
                for(size_t i = 0; i < vec3_t::components_count; i ++){
                    ost_ << v[i];
                    if(i < vec3_t::components_count - 1) ost_ << ", ";
                }
                ost_ << ")";
            }break;
            case tl::index_of<ValueTypes, vec4_t>::value:{
                const vec4_t& v = _value.get<vec4_t>();
                ost_ << "vec4(";
                for(size_t i = 0; i < vec4_t::components_count; i ++){
                    ost_ << v[i];
                    if(i < vec4_t::components_count - 1) ost_ << ", ";
                }
                ost_ << ")";
            }break;
            case tl::index_of<ValueTypes, mat2_t>::value:{
                const mat2_t& v = _value.get<mat2_t>();
                ost_ << "mat2(";
                for(size_t i = 0; i < mat2_t::components_count; i ++){
                    ost_ << v[i];
                    if(i < mat2_t::components_count - 1) ost_ << ", ";
                }
                ost_ << ")";
            }break;
            case tl::index_of<ValueTypes, mat3_t>::value:{
                const mat3_t& v = _value.get<mat3_t>();
                ost_ << "mat3(";
                for(size_t i = 0; i < mat3_t::components_count; i ++){
                    ost_ << v[i];
                    if(i < mat3_t::components_count - 1) ost_ << ", ";
                }
                ost_ << ")";
            }break;
            case tl::index_of<ValueTypes, mat4_t>::value:{
                const mat4_t& v = _value.get<mat4_t>();
                ost_ << "mat4(";
                for(size_t i = 0; i < mat4_t::components_count; i ++){
                    ost_ << v[i];
                    if(i < mat4_t::components_count - 1) ost_ << ", ";
                }
                ost_ << ")";
            }break;
            default:{
                ost_ << 0;
            }break;
        }
    }catch(BadTypeException& bte_){
        ost_ << 0;
    }
    ost_ << ";";
    
    return ost_;
}

bool Config::Parameter::parseValue(TokensSequence* tokens_)
{
    /*static const size_t _sequence_pattern_size = 2;
    static TokensSequence::Filter _sequence_pattern[_sequence_pattern_size] = {
        TokensSequence::Filter(TOKEN_, TokensSequence::AnyTokenGroup),
    };*/
    static const size_t vecs_count = 3;
    static std::string vecs[vecs_count] = {"vec2", "vec3", "vec4"};
    static size_t vecs_lens[vecs_count] = {2, 3, 4};

    static const size_t mats_count = 3;
    static std::string mats[mats_count] = {"mat2", "mat3", "mat4"};
    static size_t mats_lens[mats_count] = {4, 9, 16};
    
    if(tokens_->atEnd()) throw(UnexpectedConfigEnd(tokens_->position()));
    
    const Token* token = tokens_->peek();
    
    switch(token->id()){
        case TOKEN_OPERATOR_MINUS_ID:
        case TOKEN_OPERATOR_PLUS_ID:
        case TOKEN_NUMBER_ID:{
            Number number;
            _parseNumber(tokens_, &number);
            if(number.type == Number::Float)
                _value.set<float>(number.value.f);
            else
                _value.set<int>(number.value.i);
            //_value.set(number.type == Number::Float ? number.value.f : number.value.i);
        }break;
        case TOKEN_STRING_ID:
            _value.set(token->value());
            tokens_->skip();
            break;
        case TOKEN_NAME_ID:{
            
            std::string name = token->value();
            tokens_->skip();
            
            if(tokens_->atEnd() || tokens_->peek()->id() != TOKEN_EXPRESSION_BEGIN_ID){
                _value.set(name);
            }
            
            std::string* it, *it_beg, *it_end;
            size_t i = 0, len = 0;
            std::vector<Number> numbers;
            
            it_beg = vecs; it_end = vecs + vecs_count;
            it = std::find(it_beg, it_end, name);
            if(it != it_end){
                i = std::distance(it_beg, it);
                len = vecs_lens[i];
                
                _parseNumbersCtor(tokens_, &numbers);
                
                if(numbers.size() != len) throw(InvalidParametersCount(tokens_->position()));
                
                std::vector<float> floats(len);
                for(size_t j = 0; j < numbers.size(); j ++) floats[j] = numbers[j].toFloat();
                
                switch(len){
                    case 2:
                        _value.set<vec2_t>(vec2_t(&floats[0]));
                        break;
                    case 3:
                        _value.set<vec3_t>(vec3_t(&floats[0]));
                        break;
                    case 4:
                        _value.set<vec4_t>(vec4_t(&floats[0]));
                        break;
                }
                break;
            }
            
            it_beg = mats; it_end = mats + mats_count;
            it = std::find(it_beg, it_end, name);
            if(it != it_end){
                i = std::distance(it_beg, it);
                len = mats_lens[i];
                
                _parseNumbersCtor(tokens_, &numbers);
                
                if(numbers.size() != len) throw(InvalidParametersCount(tokens_->position()));
                
                std::vector<float> floats(len);
                for(size_t j = 0; j < numbers.size(); j ++) floats[j] = numbers[j].toFloat();
                
                switch(len){
                    case 4:
                        _value.set<mat2_t>(mat2_t(&floats[0]));
                        break;
                    case 9:
                        _value.set<mat3_t>(mat3_t(&floats[0]));
                        break;
                    case 16:
                        _value.set<mat4_t>(mat4_t(&floats[0]));
                        break;
                }
                break;
            }
            
            throw(UnknownParameterType(tokens_->position()));
        }break;
        default:
            throw(UnknownParameterType(tokens_->position()));
            break;
    }
    return true;
}

void Config::Parameter::_parseNumbersCtor(TokensSequence* tokens_, std::vector<Number>* numbers_)
{
    if(tokens_->atEnd()) throw(UnexpectedConfigEnd(tokens_->position()));
    
    const Token* token = nullptr;
    Number number;
    
    token = tokens_->peek();
    if(token->id() != TOKEN_EXPRESSION_BEGIN_ID) throw(InvalidParametersList(tokens_->position()));
    tokens_->skip();
    
    for(;;){
        if(tokens_->atEnd()) throw(UnexpectedConfigEnd(tokens_->position()));
        
        _parseNumber(tokens_, &number);
        if(numbers_) numbers_->push_back(number);
        
        if(tokens_->atEnd()) throw(UnexpectedConfigEnd(tokens_->position()));
        
        token = tokens_->peek();
        if(token->id() == TOKEN_EXPRESSION_END_ID){
            tokens_->skip();
            break;
        }else if(token->id() != TOKEN_OPERATOR_ENUMERATION_ID){
            throw(InvalidParametersList(tokens_->position()));
        }
        tokens_->skip();
    }
}

void Config::Parameter::_parseNumber(TokensSequence* tokens_, Number* number_)
{
    if(tokens_->atEnd()) throw(UnexpectedConfigEnd(tokens_->position()));
    
    const Token* token = tokens_->peek();
    bool negative = false;
    
    switch(token->id()){
        case TOKEN_OPERATOR_MINUS_ID:
            negative = true;
        case TOKEN_OPERATOR_PLUS_ID:
            tokens_->skip();
            
            if(tokens_->atEnd()) throw(UnexpectedConfigEnd(tokens_->position()));
            
            token = tokens_->peek();
            if(token->id() != TOKEN_NUMBER_ID){
                throw(BadNumberParameter(tokens_->position()));
            }
        case TOKEN_NUMBER_ID:{
            tokens_->skip();
            const CNumberToken* numbertoken = static_cast<const CNumberToken*>(token);
            if(numbertoken->fractional()){
                if(number_){
                    float res = numbertoken->toFloat();
                    if(negative) res = -res;
                    number_->value.f = res;
                    number_->type = Number::Float;
                    //std::cout << "number: " << res << std::endl;
                }
            }else{
                if(number_){
                    int res = numbertoken->toInt();
                    if(negative) res = -res;
                    number_->value.i = res;
                    number_->type = Number::Int;
                    //std::cout << "number: " << res << std::endl;
                }
            }
        }break;
        default:
            throw(BadNumberParameter(tokens_->position()));
            break;
    }
}


const std::string Config::Group::separator = ".";


Config::Group::Group()
    :Tree::Node<Config::Group>(), Element()
{
    _is_root = false;
    _parameters = new Parameters();
}

Config::Group::Group(const std::string& name_)
    :Tree::Node<Config::Group>(), Element(name_)
{
    _is_root = false;
    _parameters = new Parameters();
}

Config::Group::~Group()
{
    functions::delete_all(_parameters);
    functions::delete_all(_childs);
    delete _parameters;
}

std::ostream& Config::Group::write(std::ostream& ost_, const std::string& indent_, size_t depth_) const
{
    if(!_is_root){
        writeDepth(ost_, indent_, depth_);
        ost_ << _name << " {" << std::endl;
    }
    
    size_t new_depth = depth_ + 1;
    if(_is_root) new_depth = 0;
    
    for(Parameters::iterator it = _parameters->begin(); it != _parameters->end(); ++ it){
        (*it)->write(ost_, indent_, new_depth) << std::endl;
    }
    
    for(Childs::iterator it = _childs->begin(); it != _childs->end(); ++ it){
        (*it)->write(ost_, indent_, new_depth) << std::endl;
    }
    
    if(!_is_root){
        writeDepth(ost_, indent_, depth_);
        ost_ << "}";
    }
    return ost_;
}

bool Config::Group::isRoot() const
{
    return _is_root;
}

void Config::Group::setRoot(bool is_root_)
{
    _is_root = is_root_;
}

Config::Group* Config::Group::group(const std::string& name_)
{
    return _getSubGroup(name_, false);
}

Config::Parameter* Config::Group::parameter(const std::string& name_)
{
    return _getSubParameter(name_, false);
}

void Config::Group::addParameter(Parameter* parameter_)
{
    _parameters->push_back(parameter_);
}

bool Config::Group::removeParameter(Parameter* parameter_)
{
    Parameters::iterator it = std::find(_parameters->begin(), _parameters->end(), parameter_);
    if(it == _parameters->end()) return false;
    _parameters->erase(it);
    return true;
}

bool Config::Group::parse(TokensSequence* tokens_)
{
    static const size_t group_sequence_pattern_size = 2;
    static TokensSequence::Filter group_sequence_pattern[group_sequence_pattern_size] = {
        TokensSequence::Filter(TOKEN_NAME_ID, TokensSequence::AnyTokenGroup),
        TokensSequence::Filter(TOKEN_BLOCK_BEGIN_ID, TokensSequence::AnyTokenGroup)
    };
    
    static const size_t parameter_sequence_pattern_size = 2;
    static TokensSequence::Filter parameter_sequence_pattern[parameter_sequence_pattern_size] = {
        TokensSequence::Filter(TOKEN_NAME_ID, TokensSequence::AnyTokenGroup),
        TokensSequence::Filter(TOKEN_OPERATOR_ASSIGMENT_ID, TokensSequence::AnyTokenGroup)
    };
    
    std::string name;
    const Token* token = nullptr;
    
    for(;!tokens_->atEnd();){
    
        if(tokens_->match(group_sequence_pattern, group_sequence_pattern_size)){
            name = tokens_->peek()->value();
            tokens_->skip(group_sequence_pattern_size);
            
            //std::cout << "group: " << name << std::endl;
            
            Group* group = _getGroup(name, true);
            
            group->parse(tokens_);
            
        }else if(tokens_->match(parameter_sequence_pattern, parameter_sequence_pattern_size)){
            name = tokens_->peek()->value();
            tokens_->skip(parameter_sequence_pattern_size);
            
            //std::cout << "parameter: " << name << std::endl;
            
            Parameter* param = _getParameter(name, true);
            
            param->parseValue(tokens_);
            
            if(tokens_->atEnd()) throw(UnexpectedConfigEnd(tokens_->position()));
            token = tokens_->peek();
            if(token->id() != TOKEN_END_ID) throw(ExpectedSeparator(tokens_->position()));
            tokens_->skip();
        }else{
            token = tokens_->peek();
            if(token->id() == TOKEN_BLOCK_END_ID){
                if(_is_root) throw(ExpectedGroupDeclaration(tokens_->position()));
                tokens_->skip();
                break;
            }else if(token->id() == TOKEN_BLOCK_BEGIN_ID){
                throw(ExpectedGroupDeclaration(tokens_->position()));
            }
            throw(UnknownDeclaration(tokens_->position()));
        }
    }
    
    return true;
}     

Config::Group::parameters_iterator Config::Group::parametersBegin()
{
    return _parameters->begin();
}

Config::Group::parameters_iterator Config::Group::parametersEnd()
{
    return _parameters->end();
}

Config::Group::groups_iterator Config::Group::groupsBegin()
{
    return childsBegin();
}

Config::Group::groups_iterator Config::Group::groupsEnd()
{
    return childsEnd();
}

Config::Group* Config::Group::_getGroup(const std::string& name_, bool add_)
{
    Childs::iterator it = std::find_if(_childs->begin(), _childs->end(), NameCmp(name_));
    if(it != _childs->end()) return (*it);
    Group* res = nullptr;
    if(add_){
        res = new Group(name_);
        addChild(res);
    }
    return res;
}

Config::Parameter* Config::Group::_getParameter(const std::string& name_, bool add_)
{
    Parameters::iterator it = std::find_if(_parameters->begin(), _parameters->end(), NameCmp(name_));
    if(it != _parameters->end()) return (*it);
    Parameter* res = nullptr;
    if(add_){
        res = new Parameter(name_);
        addParameter(res);
    }
    return res;
}

Config::Group* Config::Group::_getSubGroup(const std::string& name_, bool add_)
{
    size_t pos = name_.find(separator);
    if(pos == std::string::npos){
        return _getGroup(name_, add_);
    }
    std::string grp_name = name_.substr(0, pos);
    Group* grp = _getGroup(grp_name, add_);
    if(grp){
        return grp->_getSubGroup(name_.substr(pos + separator.size()), add_);
    }
    return nullptr;
}

Config::Parameter* Config::Group::_getSubParameter(const std::string& name_, bool add_)
{
    size_t pos = name_.rfind(separator);
    if(pos == std::string::npos){
        return _getParameter(name_, add_);
    }
    std::string grp_name = name_.substr(0, pos);
    Group* grp = _getSubGroup(grp_name, add_);
    if(grp){
        return grp->_getParameter(name_.substr(pos + separator.size()), add_);
    }
    return nullptr;
}



Config::Config()
{
    _createTokenizer();
    _root = new Group();
    _root->setRoot(true);
}

Config::~Config()
{
    _delTokenizer();
    delete _root;
}

bool Config::read(const std::string& filename_)
{
    std::fstream fst(filename_, std::ios::in);
    if(!fst) return false;
    
    std::istreambuf_iterator<char> it_ist(fst), it_eos;
    
    return parse(std::string(it_ist, it_eos));
}

bool Config::parse(const std::string& source_)
{
    return _parse(source_);
}

bool Config::write(const std::string& filename_) const
{
    std::fstream fst(filename_, std::ios::out);
    if(!fst) return false;
    
    _root->write(fst, std::string("    "), 0);
    
    return true;
}

Config::Group* Config::group(const std::string& name_)
{
    return _root->group(name_);
}

Config::Parameter* Config::parameter(const std::string& name_)
{
    return _root->parameter(name_);
}

void Config::_createTokenParsers(TokenParsers* tps_)
{
    //tps_->push_back(std::make_pair(0, new TokenParser()));
    //ws
    tps_->push_back(std::make_pair(0, new SequenceTokenParser("/*", "*/", TOKEN_C_COMMENT_ID, TOKEN_SPACES_GID)));
    tps_->push_back(std::make_pair(0, new SequenceTokenParser("//", "\n", true, TOKEN_CPP_COMMENT_ID, TOKEN_SPACES_GID)));
    /*tps_->push_back(std::make_pair(0, new WordTokenParser("\n", TOKEN_NEWLINE_ID, TOKEN_SPACES_GID)));
    tps_->push_back(std::make_pair(0, new WordTokenParser(" ", TOKEN_SPACE_ID, TOKEN_SPACES_GID)));
    tps_->push_back(std::make_pair(0, new WordTokenParser("\t", TOKEN_TAB_ID, TOKEN_SPACES_GID)));*/
    tps_->push_back(std::make_pair(0, new DelimitersTokenParser("\t \n\r", TOKEN_DELIMITERS_ID, TOKEN_SPACES_GID)));
    //values
    tps_->push_back(std::make_pair(10, new CNameTokenParser(TOKEN_NAME_ID, TOKEN_VALUES_GID)));
    tps_->push_back(std::make_pair(10, new CNumberTokenParser(CNumberTokenParser::DOT, TOKEN_NUMBER_ID, TOKEN_VALUES_GID)));
    tps_->push_back(std::make_pair(10, new CStringTokenParser("\"", "\"", TOKEN_STRING_ID, TOKEN_VALUES_GID)));
    //operators
    tps_->push_back(std::make_pair(1, new WordTokenParser("=", TOKEN_OPERATOR_ASSIGMENT_ID, TOKEN_OPERATORS_GID)));
    tps_->push_back(std::make_pair(1, new WordTokenParser("+", TOKEN_OPERATOR_PLUS_ID, TOKEN_OPERATORS_GID)));
    tps_->push_back(std::make_pair(1, new WordTokenParser("-", TOKEN_OPERATOR_MINUS_ID, TOKEN_OPERATORS_GID)));
    tps_->push_back(std::make_pair(1, new WordTokenParser(",", TOKEN_OPERATOR_ENUMERATION_ID, TOKEN_OPERATORS_GID)));
    //blocks
    tps_->push_back(std::make_pair(1, new WordTokenParser("(", TOKEN_EXPRESSION_BEGIN_ID, TOKEN_BLOCKS_GID)));
    tps_->push_back(std::make_pair(1, new WordTokenParser(")", TOKEN_EXPRESSION_END_ID, TOKEN_BLOCKS_GID)));
    tps_->push_back(std::make_pair(1, new WordTokenParser(";", TOKEN_END_ID, TOKEN_BLOCKS_GID)));
    tps_->push_back(std::make_pair(1, new WordTokenParser("{", TOKEN_BLOCK_BEGIN_ID, TOKEN_BLOCKS_GID)));
    tps_->push_back(std::make_pair(1, new WordTokenParser("}", TOKEN_BLOCK_END_ID, TOKEN_BLOCKS_GID)));
}

void Config::_addTokenParsers(Tokenizer* tokenizer_, TokenParsers* tps_)
{
    std::for_each(tps_->begin(), tps_->end(), [tokenizer_](TokenParserPair& tp){
        tokenizer_->addTokenParser(tp.first, tp.second);
    });
}

void Config::_delTokenParsers(TokenParsers* tps_)
{
    std::for_each(tps_->begin(), tps_->end(), [](TokenParserPair& tp){
        delete tp.second;
    });
    tps_->clear();
}

void Config::_createTokenizer()
{
    _tokenparsers = new TokenParsers();
    _createTokenParsers(_tokenparsers);
    
    _tokenizer = new Tokenizer();
    _tokenizer->setSkipUnknownTokens(false);
    
    _addTokenParsers(_tokenizer, _tokenparsers);
}

void Config::_delTokenizer()
{
    _delTokenParsers(_tokenparsers);
    delete _tokenparsers;
    delete _tokenizer;
}

bool Config::_parse(const std::string& source_)
{
    _tokenizer->clearTokens();
    _tokenizer->setSource(source_);
    
    if(!_tokenizer->parse()) return false;
    
    _removeSpacesTokens();
    
    TokensSequence tokens(_tokenizer);
    
    return _root->parse(&tokens);
}

void Config::_removeSpacesTokens()
{
    for(Tokenizer::iterator it = _tokenizer->tokensBegin();
            it != _tokenizer->tokensEnd();){
        if((*it)->gid() == TOKEN_SPACES_GID){
            Tokenizer::iterator it_cur = it ++;
            _tokenizer->removeToken(it_cur);
        }else{
            ++ it;
        }
    }
}

