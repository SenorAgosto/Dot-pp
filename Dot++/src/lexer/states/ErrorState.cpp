#include <Dot++/states/ErrorState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

namespace dot_pp { namespace states {
    
    TokenizerState ErrorState::consume(const char, FileInfo&, Token&, std::deque<TokenInfo>&) const
    {
        return TokenizerState::Error;
    }
}}
