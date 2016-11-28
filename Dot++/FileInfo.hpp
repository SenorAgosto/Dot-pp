#pragma once 
#include <Dot++/LineInfo.hpp>
#include <string>

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
        
        const LineInfo& start() const { return start_; }
        
        void end(const LineInfo& lineInfo) { end_ = lineInfo; }
        const LineInfo& end() const { return end_; }
    
    private:
        FileInfo& operator=(const FileInfo& info) = delete;
        
    private:
        std::string filename_;
        
        const LineInfo start_;
        LineInfo end_;
    };
}
