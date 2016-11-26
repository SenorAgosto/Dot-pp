#pragma once

#include <Dot++/FileInfo.hpp>
#include <Dot++/TokenType.hpp>
#include <string> 

namespace dot_pp {

    class Token
    {
    public:
        Token(const FileInfo& info);
        Token(const FileInfo& info, const std::string& value, const TokenType type);

        void info(const FileInfo& info) { info_ = info; }
        const FileInfo& info() const { return info_; }
        FileInfo& info() { return info_; }
        
        void type(const TokenType type) { type_ = type; }
        TokenType type() const { return type_; }

        void append(const char c) { value_.append(1, c); }
        
        bool empty() const { return value_.empty(); }
        const std::string& to_string() const { return value_; }
        
    private:
        FileInfo info_;
        
        std::string value_;
        TokenType type_;
    };
}
