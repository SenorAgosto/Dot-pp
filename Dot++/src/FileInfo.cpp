#include <Dot++/FileInfo.hpp>
#include <utility>

namespace dot_pp {

    FileInfo::FileInfo(const std::string& filename)
        : filename_(filename)
    {
    }
    
    FileInfo::FileInfo(const std::string& filename, const LineInfo& start)
        : filename_(filename)
        , start_(start)
    {
    }
    
    FileInfo::FileInfo(const std::string& filename, const LineInfo& start, const LineInfo& end)
        : filename_(filename)
        , start_(start)
        , end_(end)
    {
    }
    
    FileInfo::FileInfo(const FileInfo& info)
        : filename_(info.filename_)
        , start_(info.start_)
        , end_(info.end_)
    {
    }
    
    FileInfo::FileInfo(FileInfo&& info)
        : filename_(std::move(info.filename_))
        , start_(info.start_)
        , end_(std::move(info.end_))
    {
    }    
}
