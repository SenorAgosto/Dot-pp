#include <Dot++/states/SlashLineCommentState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    TokenizerState SlashLineCommentState::consume(const char c, FileInfo& info, Token& token, std::deque<TokenInfo>& tokens) const
    {
        if(c == '\n')
        {
            if(token.type() != TokenType::multiline_comment)
            {
                token.type(TokenType::comment);
            }
            
            return produceToken(TokenizerState::Init, tokens, token, info);
        }
        
        // multiline escape sequance
        if(c == '\\')
        {
            token.type(TokenType::multiline_comment);
            return TokenizerState::MultiLineEscape;
        }
        
        // ignore second slash
        if(c == '/')
        {
            return TokenizerState::SlashLineComment;
        }

        if(c == '*')
        {
            return TokenizerState::MultiLineComment;
        }
        
        token.append(c);
        return TokenizerState::SlashLineComment;
    }
}}
