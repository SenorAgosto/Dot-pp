#include <Dot++/TokenInfo.hpp>

namespace dot_pp {

    TokenInfo::TokenInfo(const std::string& filename)
        : filename_(filename)
    {
    }
    
    TokenInfo::TokenInfo(const std::string& filename, const LineInfo& start, const LineInfo& end)
        : filename_(filename)
        , start_(start)
        , end_(end)
    {
    }    
}
