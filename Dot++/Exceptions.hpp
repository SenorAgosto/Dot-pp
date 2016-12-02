#pragma once
#include <stdexcept>

namespace dot_pp { namespace lexer {
    class TokenInfo;
    enum class TokenizerState;
}}

namespace dot_pp {
    
    class ParserError : public std::runtime_error
    {
    public:
        ParserError(const std::string& reason);
    };
    
    class TokenizerError : public std::runtime_error
    {
    public:
        TokenizerError(const std::string& reason);
    };
    
    class UnknownTokenizerState : public TokenizerError
    {
    public:
        UnknownTokenizerState(const lexer::TokenizerState state);
    };
    
    class SyntaxError : public ParserError
    {
    public:
        SyntaxError(const std::string& error, const lexer::TokenInfo& token);
    };
}
