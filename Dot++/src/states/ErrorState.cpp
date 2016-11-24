#include <Dot++/states/ErrorState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

namespace dot_pp {
    
    TokenizerState ErrorState::consume(const char, Token&) const
    {
        return TokenizerState::Error;
    }
}
