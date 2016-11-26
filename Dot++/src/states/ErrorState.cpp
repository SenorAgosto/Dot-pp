#include <Dot++/states/ErrorState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

namespace dot_pp { namespace states {
    
    TokenizerState ErrorState::consume(const char, Token&, std::deque<Token>&) const
    {
        return TokenizerState::Error;
    }
}}
