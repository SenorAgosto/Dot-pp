#include <Dot++/lexer/states/ErrorState.hpp>

#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

namespace dot_pp { namespace lexer { namespace states {
    
    TokenizerState ErrorState::consume(const char, FileInfo&, Token&, std::deque<TokenInfo>&) const
    {
        return TokenizerState::Error;
    }
}}}
