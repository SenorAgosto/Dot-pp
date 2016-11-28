#include <Dot++/states/HashLineCommentState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    TokenizerState HashLineCommentState::consume(const char c, FileInfo& info, Token& token, std::deque<TokenInfo>& tokens) const
    {
        if(c == '\n')
        {
            token.type(TokenType::comment);
            return produceToken(TokenizerState::Init, info, tokens, token);
        }

        // ignore carriage returns
        if(c == '\r')
        {
            return TokenizerState::HashLineComment;
        }

        token.append(c);
        return TokenizerState::HashLineComment;
    }
}}
