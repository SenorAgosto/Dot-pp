#pragma once 
#include <Dot++/LineInfo.hpp>

#include <cstddef>
#include <string>

namespace dot_pp {
    class Token;
}

namespace dot_pp {

    // Information about where a token starts and ends
    class FileInfo
    {
    public:
        FileInfo(const std::string& filename);
        FileInfo(const std::string& filename, const LineInfo& start);
        FileInfo(const std::string& filename, const LineInfo& start, const LineInfo& end);
    
        FileInfo(const FileInfo& info);
        FileInfo(FileInfo&& info);
        
        const std::string& filename() const { return filename_; }
        const LineInfo& start() const { return start_; }
        const LineInfo& end() const { return end_; }
        
        void incrementLine() { end_.incrementLine(); }
        void incrementColumn() { end_.incrementColumn(); }
        void incrementColumnBy(const std::size_t count) { end_.incrementColumnBy(count); }
        void advanceBy(const Token& token);
        
        bool empty() const { return start_ == end_; }
        
    private:
        FileInfo& operator=(const FileInfo& info) = delete;
        
    private:
        std::string filename_;
        
        const LineInfo start_;
        LineInfo end_;
    };
}
