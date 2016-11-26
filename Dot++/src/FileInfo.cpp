#include <Dot++/FileInfo.hpp>

namespace dot_pp {

    FileInfo::FileInfo(const std::string& filename)
        : filename_(filename)
    {
    }
    
    FileInfo::FileInfo(const std::string& filename, const LineInfo& start, const LineInfo& end)
        : filename_(filename)
        , start_(start)
        , end_(end)
    {
    }    
}
