#include <Dot++/lexer/Token.hpp>

namespace dot_pp { namespace lexer {
    
    Token::Token()
        : type_(TokenType::string)
    {
    }
    
    Token::Token(const std::string& value, const TokenType type)
        : value_(value)
        , type_(type)
    {
    }
    
    bool Token::empty() const
    {
        if(type_ == TokenType::string_literal)
        {
            return false;
        }
        
        for(const auto c : value_)
        {
            if((c != '\n') && (c != '\r') && (c != '\t') && (c != ' '))
            {
                return false;
            }
        }
        
        return true;
    }
    
    void Token::clear()
    {
        value_.clear();
        type_ = TokenType::string;
    }
}}
