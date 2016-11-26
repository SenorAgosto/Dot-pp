#pragma once

#include <Dot++/TokenInfo.hpp>
#include <Dot++/TokenType.hpp>
#include <string> 

namespace dot_pp {

    class Token
    {
    public:
        Token(const TokenInfo& info);
        Token(const TokenInfo& info, const std::string& value, const TokenType type);

        void info(const TokenInfo& info) { info_ = info; }
        const TokenInfo& info() const { return info_; }
        TokenInfo& info() { return info_; }
        
        void type(const TokenType type) { type_ = type; }
        TokenType type() const { return type_; }

        void append(const char c) { value_.append(1, c); }
        
        bool empty() const { return value_.empty(); }
        const std::string& to_string() const { return value_; }
        
    private:
        TokenInfo info_;
        
        std::string value_;
        TokenType type_;
    };
}
