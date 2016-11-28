#include <Dot++/states/MultiLineEscapeState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    TokenizerState MultiLineEscapeState::consume(const char c, FileInfo&, Token& token, std::deque<TokenInfo>&) const
    {
        if(c == '\n')
        {
            token.type(TokenType::multiline_comment);
            return TokenizerState::SlashLineComment;
        }
        
        return TokenizerState::Error;
    }
}}
