#pragma once 
#include <Dot++/TokenizerStateInterface.hpp>
#include <Dot++/TokenType.hpp>

#include <deque>

namespace dot_pp {
    enum class TokenizerState;
    class Token;
}

namespace dot_pp {
    
    class InitialState : public TokenizerStateInterface
    {
    public:
        TokenizerState consume(const char c, Token& token, std::deque<Token>& tokens) const override;
    };
}
