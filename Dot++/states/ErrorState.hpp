#pragma once
#include <Dot++/TokenizerStateInterface.hpp>

namespace dot_pp { namespace states {
    
    class ErrorState : public TokenizerStateInterface
    {
    public:
        TokenizerState consume(const char c, FileInfo& info, Token& token, std::deque<TokenInfo>& tokens) const override;
    };
}}
