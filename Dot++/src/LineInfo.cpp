#include <Dot++/LineInfo.hpp>

namespace dot_pp {

    LineInfo::LineInfo()
        : line_(0)
        , column_(0)
    {
    }

    LineInfo::LineInfo(const std::size_t line, const std::size_t column)
        : line_(line)
        , column_(column)
    {
    }
}
