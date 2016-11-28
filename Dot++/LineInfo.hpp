#pragma once 
#include <cstddef>

namespace dot_pp {

    class LineInfo
    {
    public:
        LineInfo();
        LineInfo(const std::size_t line, const std::size_t column);
        
        std::size_t line() const { return line_; }
        std::size_t column() const { return column_; }
        
        void incrementColumn() { column_++; }
        void incrementLine() { line_++; column_ = 1; }
        
    private:
        std::size_t line_;
        std::size_t column_;
    };
}
