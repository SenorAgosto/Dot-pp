#include <Dot++/states/EndMultiLineCommentState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp {
    
    TokenizerState EndMultiLineCommentState::consume(const char c, Token& token, std::deque<Token>& tokens) const
    {
        if(c == '/')
        {
            token.type(TokenType::multiline_comment);
            return produceToken(TokenizerState::Init, tokens, std::move(token));
        }
        
        token.append(c);
        return TokenizerState::MultiLineComment;
    }
}
