#pragma once 
#include <Dot++/LineInfo.hpp>
#include <string>

namespace dot_pp {

    class FileInfo
    {
    public:
        FileInfo(const std::string& filename);
        FileInfo(const std::string& filename, const LineInfo& start, const LineInfo& end);
                
        void start(const LineInfo& lineInfo) { start_ = lineInfo; }
        const LineInfo& start() const { return start_; }
        
        void end(const LineInfo& lineInfo) { end_ = lineInfo; }
        const LineInfo& end() const { return end_; }
        
    private:
        std::string filename_;
        
        LineInfo start_;
        LineInfo end_;
    };
}
