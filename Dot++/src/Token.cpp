#include <Dot++/Token.hpp>

namespace dot_pp {
    
    Token::Token()
        : type_(TokenType::string)
    {
    }
    
    Token::Token(const std::string& value, const TokenType type)
        : value_(value)
        , type_(type)
    {
    }
}
