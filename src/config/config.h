#ifndef CONFIG_H
#define	CONFIG_H

#include <string>
#include <list>
#include <vector>
#include <utility>
#include <stddef.h>
#include "tree/tree_node.h"
#include "tlvariant/tlvariant.h"
#include "glmath/glmath.h"
#include "tokenizer/token.h"
#include "tokenizer/tokenizer.h"

//#include <iostream>


class TokenParser;
class TokensSequence;


class Config {
public:
    
    class Element{
    public:
        
        Element();
        Element(const std::string& name_);
        virtual ~Element();
        
        const std::string& name() const;
        void setName(const std::string& name_);
        
        virtual std::ostream& write(std::ostream& ost_, const std::string& indent_, size_t depth_) const = 0;
        virtual std::ostream& writeDepth(std::ostream& ost_, const std::string& indent_, size_t depth_) const;
    protected:
        std::string _name;
    };
    
    typedef tl::makeTypeList<int, float, std::string,
                             vec2_t, vec3_t, vec4_t,
                             mat2_t, mat3_t, mat4_t>::value ValueTypes;
    typedef TLVariant<ValueTypes> Value;
    
    class Parameter
        :public Element
    {
    public:
        Parameter();
        Parameter(const std::string& name_);
        ~Parameter();
        
        bool parseValue(TokensSequence* tokens_);
        
        template<class T>
        T value(const T& defval_) const;
        
        template<class T>
        bool setValue(const T& val_);
        
        std::ostream& write(std::ostream& ost_, const std::string& indent_, size_t depth_) const;
        
    private:
        Value _value;
        
        struct Number{
            enum Type{Int, Float};
            Type type;
            union{
                float f;
                int i;
            }value;
            
            float toFloat(){
                if(type == Float) return value.f;
                return static_cast<float>(value.i);
            }
            float toInt(){
                if(type == Int) return value.i;
                return static_cast<int>(value.f);
            }
        };
        
        void _parseNumbersCtor(TokensSequence* tokens_, std::vector<Number>* numbers_);
        void _parseNumber(TokensSequence* tokens_, Number* number_);
    };
    
    class Group
        :public Tree::Node<Config::Group>, public Element
    {
    public:
        
        static const std::string separator;
        
        Group();
        Group(const std::string& name_);
        ~Group();
        
        template<class T> 
        T value(const std::string& name_, const T& defval_ = T()) const;
        
        template<class T> 
        bool setValue(const std::string& name_, const T& val_);
        
        bool isRoot() const;
        void setRoot(bool is_root_);
        
        void addParameter(Parameter* parameter_);
        
        bool parse(TokensSequence* tokens_);
        
        std::ostream& write(std::ostream& ost_, const std::string& indent_, size_t depth_) const;
    private:
        typedef std::list<Parameter*> Parameters;
        Parameters* _parameters;
        
        bool _is_root;
        
        struct NameCmp{
            NameCmp(const std::string& name_){
                _name = name_;
            }
            bool operator()(const Element* e_){
                return _name == e_->name();
            }
            std::string _name;
        };
        
        Group* _getGroup(const std::string& name_, bool add_);
        Parameter* _getParameter(const std::string& name_, bool add_);
        
        Group* _getSubGroup(const std::string& name_, bool add_);
        Parameter* _getSubParameter(const std::string& name_, bool add_);
    };
    
    
    Config();
    ~Config();
    
    bool read(const std::string& filename_);
    bool parse(const std::string& source_);
    bool write(const std::string& filename_) const;
    
    template<class T> 
    T value(const std::string& name_, const T& defval_ = T()) const;

    template<class T> 
    bool setValue(const std::string& name_, const T& val_);
    
private:
    
    typedef std::pair<tokenprior_t, TokenParser*> TokenParserPair;
    typedef std::list<TokenParserPair> TokenParsers;
    
    TokenParsers* _tokenparsers;
    Tokenizer* _tokenizer;
    
    Group* _root;

    void _createTokenParsers(TokenParsers* tps_);
    void _addTokenParsers(Tokenizer* tokenizer_, TokenParsers* tps_);
    void _delTokenParsers(TokenParsers* tps_);
    void _createTokenizer();
    void _delTokenizer();
    bool _parse(const std::string& source_);
    void _removeSpacesTokens();
    
};


template<class T>
T Config::Parameter::value(const T& defval_) const
{
    try{
        return _value.get<T>();
    }catch(BadTypeException& bte_){
        return defval_;
    }
}

template<class T>
bool Config::Parameter::setValue(const T& val_)
{
    try{
        _value.set<T>(val_);
    }catch(BadTypeException& bte_){
        return false;
    }
    return true;
}

template<class T>
T Config::Group::value(const std::string& name_, const T& defval_) const
{
    Parameter* param = const_cast<Config::Group*>(this)->_getSubParameter(name_, false);
    if(param) return param->value<T>(defval_);
    return defval_;
}

template<class T> 
bool Config::Group::setValue(const std::string& name_, const T& val_)
{
    return _getSubParameter(name_, true)->setValue<T>(val_);
}


template<class T>
T Config::value(const std::string& name_, const T& defval_) const
{
    return _root->value<T>(name_, defval_);
}

template<class T> 
bool Config::setValue(const std::string& name_, const T& val_)
{
    return _root->setValue<T>(name_, val_);
}



#endif	/* CONFIG_H */

