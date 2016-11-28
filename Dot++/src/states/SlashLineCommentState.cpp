#include <Dot++/states/SlashLineCommentState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    TokenizerState SlashLineCommentState::consume(const char c, FileInfo& info, Token& token, std::deque<TokenInfo>& tokens) const
    {
        if(c == '\n')
        {
            token.type(TokenType::comment);
            return produceToken(TokenizerState::Init, info, tokens, token);
        }
        
        // multiline escape sequance
        if(c == '\\')
        {
            token.type(TokenType::multiline_comment);
            return TokenizerState::MultiLineEscape;
        }
        
        token.append(c);
        return TokenizerState::SlashLineComment;
    }
}}
