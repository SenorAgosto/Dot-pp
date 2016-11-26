#include <Dot++/Token.hpp>

namespace dot_pp {
    
    Token::Token(const FileInfo& info)
        : info_(info)
        , type_(TokenType::string)
    {
    }
    
    Token::Token(const FileInfo& info, const std::string& value, const TokenType type)
        : info_(info)
        , value_(value)
        , type_(type)
    {
    }
}
