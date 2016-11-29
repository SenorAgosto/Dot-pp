#include <Dot++/FileInfo.hpp>
#include <Dot++/Token.hpp>

#include <utility>

namespace dot_pp {

    FileInfo::FileInfo(const std::string& filename)
        : filename_(filename)
    {
    }
    
    FileInfo::FileInfo(const std::string& filename, const LineInfo& start)
        : filename_(filename)
        , start_(start)
        , end_(start)
    {
    }
    
    FileInfo::FileInfo(const std::string& filename, const LineInfo& start, const LineInfo& end)
        : filename_(filename)
        , start_(start)
        , end_(end)
    {
    }

    void FileInfo::advanceBy(const Token& token)
    {
        for(const auto c : token.to_string())
        {
            if(c == '\n')
            {
                end_.incrementLine();
            }
            else
            {
                end_.incrementColumn();
            }
        }
    }
}
