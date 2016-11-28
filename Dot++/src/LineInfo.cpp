#include <Dot++/LineInfo.hpp>

namespace dot_pp {

    LineInfo::LineInfo()
        : line_(1)
        , column_(1)
    {
    }

    LineInfo::LineInfo(const std::size_t line, const std::size_t column)
        : line_(line)
        , column_(column)
    {
    }
    
    bool operator<(const LineInfo& lhs, const LineInfo& rhs)
    {
        return lhs.line() == rhs.line() ?
            lhs.column() < rhs.column() :
            lhs.line() < rhs.line();
    }
    
    bool operator==(const LineInfo& lhs, const LineInfo& rhs)
    {
        return (lhs.line() == rhs.line()) && (lhs.column() == rhs.column());
    }
    
    bool operator>(const LineInfo& lhs, const LineInfo& rhs)
    {
        return lhs.line() == rhs.line() ?
            lhs.column() > rhs.column() :
            lhs.line() > rhs.line();
    }
}
