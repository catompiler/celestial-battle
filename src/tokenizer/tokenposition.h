#ifndef TOKENPOSITION_H
#define	TOKENPOSITION_H

#include <stddef.h>

class TokenPosition
{
public:
    TokenPosition();
    TokenPosition(size_t offset_, size_t line_, size_t col_);
    TokenPosition(const TokenPosition& pos_);
    ~TokenPosition();

    TokenPosition& operator=(const TokenPosition& pos_);
    bool operator==(const TokenPosition& pos_) const;

    size_t offset() const;
    void setOffset(size_t offset_);
    void incOffset(){_offset ++;}
    
    size_t line() const;
    void setLine(size_t line_);
    void incLine(){_line ++;}
    
    size_t col() const;
    void setCol(size_t col_);
    void incCol(){_col ++;}
    
    void reset();
    
protected:
    
    size_t _offset;
    size_t _line;
    size_t _col;
};

#endif	/* TOKENPOSITION_H */

