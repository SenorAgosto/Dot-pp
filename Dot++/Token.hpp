#pragma once
#include <Dot++/TokenType.hpp>
#include <string> 

namespace dot_pp {

    class Token
    {
    public:
        Token();

        void type(const TokenType type) { type_ = type; }
        TokenType type() const { return type_; }

        void append(const char c) { value_.append(1, c); }
        void clear();
        
        void produce() { ready_ = true; }
        bool ready() const { return ready_; }
        
        bool empty() const { return value_.empty(); }
        const std::string& to_string() const { return value_; }
        
        void swap(Token& t);
        
    private:
        std::string value_;
        
        TokenType type_;
        bool ready_;    // set true when token is complete
    };
}
