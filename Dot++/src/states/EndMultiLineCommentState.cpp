#include <Dot++/states/EndMultiLineCommentState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    TokenizerState EndMultiLineCommentState::consume(const char c, FileInfo& info, Token& token, std::deque<TokenInfo>& tokens) const
    {        
        if(c == '/')
        {
            token.type(TokenType::multiline_comment);
            return produceToken(TokenizerState::Init, tokens, token, info);
        }
        
        token.append(c);
        return TokenizerState::MultiLineComment;
    }
}}
