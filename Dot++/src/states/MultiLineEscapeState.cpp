#include <Dot++/states/MultiLineEscapeState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp {
    
    TokenizerState MultiLineEscapeState::consume(const char c, Token& token, std::deque<Token>&) const
    {
        if(c == '\n')
        {
            token.type(TokenType::multiline_comment);
            return TokenizerState::SlashLineComment;
        }
        
        return TokenizerState::Error;
    }
}
