#include "tokenposition.h"


TokenPosition::TokenPosition()
{
    reset();
}

TokenPosition::TokenPosition(size_t offset_, size_t line_, size_t col_)
{
    _offset = offset_;
    _line = line_;
    _col = col_;
}

TokenPosition::TokenPosition(const TokenPosition& pos_)
{
    _offset = pos_._offset;
    _line = pos_._line;
    _col = pos_._col;
}

TokenPosition::~TokenPosition()
{
}

TokenPosition& TokenPosition::operator=(const TokenPosition& pos_)
{
    _offset = pos_._offset;
    _line = pos_._line;
    _col = pos_._col;
    
    return *this;
}

bool TokenPosition::operator==(const TokenPosition& pos_) const
{
    return _offset == pos_._offset &&
           _line == pos_._line &&
           _col == pos_._col;
}

size_t TokenPosition::offset() const
{
    return _offset;
}

void TokenPosition::setOffset(size_t offset_)
{
    _offset = offset_;
}

size_t TokenPosition::line() const
{
    return _line;
}

void TokenPosition::setLine(size_t line_)
{
    _line = line_;
}

size_t TokenPosition::col() const
{
    return _col;
}

void TokenPosition::setCol(size_t col_)
{
    _col = col_;
}

void TokenPosition::reset()
{
    _offset = 0;
    _line = 0;
    _col = 0;
}

