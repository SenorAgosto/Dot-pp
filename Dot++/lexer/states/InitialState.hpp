#pragma once 
#include <Dot++/lexer/TokenizerStateInterface.hpp>

namespace dot_pp { namespace lexer { namespace states {
    
    class InitialState : public TokenizerStateInterface
    {
    public:
        TokenizerState consume(const char c, FileInfo& info, Token& token, std::deque<TokenInfo>& tokens) const override;
    };
}}}
