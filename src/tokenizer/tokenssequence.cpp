#include "tokenssequence.h"
#include "token.h"
#include <algorithm>



TokensSequence::Filter::Filter(tokenid_t id_, tokenid_t gid_, bool required_)
{
    _id = id_;
    _gid = gid_;
    _required = required_;
}

TokensSequence::Filter::Filter(const Filter& filter_)
{
    _id = filter_._id;
    _gid = filter_._gid;
    _required = filter_._required;
}

TokensSequence::Filter::~Filter()
{
}

tokenid_t TokensSequence::Filter::id() const
{
    return _id;
}

void TokensSequence::Filter::setId(tokenid_t id_)
{
    _id = id_;
}

tokenid_t TokensSequence::Filter::gid() const
{
    return _gid;
}

void TokensSequence::Filter::setGid(tokenid_t gid_)
{
    _gid = gid_;
}

bool TokensSequence::Filter::required() const
{
    return _required;
}

void TokensSequence::Filter::setRequired(bool required_)
{
    _required = required_;
}

bool TokensSequence::Filter::match(const Token* token_)
{
    return match(token_->id(), token_->gid());
}

bool TokensSequence::Filter::match(tokenid_t id_, tokenid_t gid_)
{
    bool m_id = _id == AnyToken ? true : _id == id_;
    bool m_gid = _gid == AnyTokenGroup ? true : _gid == gid_;
    
    return m_id && m_gid;
}

TokensSequence::Filter& TokensSequence::Filter::operator=(const Filter& filter_)
{
    _id = filter_._id;
    _gid = filter_._gid;
    _required = filter_._required;
    
    return *this;
}

bool TokensSequence::Filter::operator==(const Filter& filter_) const
{
    return _id == filter_._id &&
           _gid == filter_._gid &&
           _required == filter_._required;
}


TokensSequence::TokensSequence(const Tokenizer* tokenizer_)
{
    _tokenizer = tokenizer_;
    _it_beg = tokenizer_->tokensBegin();
    _it_cur = tokenizer_->tokensBegin();
    _it_end = tokenizer_->tokensEnd();
}

TokensSequence::~TokensSequence()
{
}

bool TokensSequence::atEnd() const
{
    return _it_cur == _it_end;
}

bool TokensSequence::hasTokens() const
{
    return !atEnd();
}

const TokenPosition& TokensSequence::position() const
{
    return atEnd() ? _tokenizer->position() : (*_it_cur)->pos();
}

size_t TokensSequence::remaining() const
{
    return std::distance(_it_cur, _it_end);
}

bool TokensSequence::match(Filter* sequence_, size_t count_) const
{
    if(remaining() < count_) return false;
    
    iterator it = _it_cur;
    
    for(size_t i = 0; i < count_; i ++){
        if(sequence_[i].match(*it)){
            ++ it;
            continue;
        }else{
            if(sequence_[i].required()) return false;
        }
    }
    return true;
}

const Token* TokensSequence::peek()
{
    return hasTokens() ? *_it_cur : NULL;
}

const Token* TokensSequence::get()
{
    return hasTokens() ? *_it_cur ++ : NULL;
}

void TokensSequence::skip()
{
    skip(1);
}

void TokensSequence::skip(size_t n_)
{
    std::advance(_it_cur, std::min(n_, remaining()));
}
