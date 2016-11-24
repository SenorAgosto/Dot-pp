#pragma once
#include <stdexcept>

namespace dot_pp {
    enum class TokenizerState;
}

namespace dot_pp {
    
    class TokenizerError : public std::runtime_error
    {
    public:
        TokenizerError(const std::string& reason);
    };
    
    class UnknownTokenizerState : public TokenizerError
    {
    public:
        UnknownTokenizerState(const TokenizerState state);
    };
}
