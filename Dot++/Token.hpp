#pragma once

#include <Dot++/FileInfo.hpp>
#include <Dot++/TokenType.hpp>
#include <string> 

namespace dot_pp {

    class Token
    {
    public:
        Token();
        Token(const std::string& value, const TokenType type);
        
        void type(const TokenType type) { type_ = type; }
        TokenType type() const { return type_; }

        void append(const char c) { value_.append(1, c); }
        
        bool empty() const { return value_.empty(); }
        const std::string& to_string() const { return value_; }
        
        void clear();
        
    private:
        std::string value_;
        TokenType type_;
    };
}
