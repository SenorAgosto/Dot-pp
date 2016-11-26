#include <Dot++/states/SlashLineCommentState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp {
    
    TokenizerState SlashLineCommentState::consume(const char c, Token& token, std::deque<Token>& tokens) const
    {
        if(c == '\n')
        {
            token.type(TokenType::comment);
            return produceToken(TokenizerState::Init, tokens, std::move(token));
        }
        
        // multiline escape sequance
        if(c == '\\')
        {
            return TokenizerState::MultiLineEscape;
        }
        
        token.append(c);
        return TokenizerState::SlashLineComment;
    }
}
