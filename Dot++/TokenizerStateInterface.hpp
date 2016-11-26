#pragma once 
#include <deque>

namespace dot_pp {
    class Token;
    enum class TokenizerState;
}

namespace dot_pp {
    
    class TokenizerStateInterface
    {
    public:
        virtual ~TokenizerStateInterface() {}
        virtual TokenizerState consume(const char c, Token& token, std::deque<Token>& tokens) const = 0;
    };
}
