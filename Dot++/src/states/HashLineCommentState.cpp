#include <Dot++/states/HashLineCommentState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp {
    
    TokenizerState HashLineCommentState::consume(const char c, Token& token, std::deque<Token>& tokens) const
    {
        if(c == '\n')
        {
            token.type(TokenType::comment);
            return produceToken(TokenizerState::Init, tokens, std::move(token));
        }

        // ignore carriage returns
        if(c == '\r')
        {
            return TokenizerState::HashLineComment;
        }

        token.append(c);
        return TokenizerState::HashLineComment;
    }
}
