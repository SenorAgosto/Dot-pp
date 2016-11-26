#include <Dot++/states/BeginSlashLineCommentState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    TokenizerState BeginSlashLineCommentState::consume(const char c, Token& token, std::deque<Token>& tokens) const
    {
        if(c == '/')
        {
            return produceToken(TokenizerState::SlashLineComment, tokens, std::move(token));
        }
        
        if(c == '*')
        {
            return produceToken(TokenizerState::MultiLineComment, tokens, std::move(token));
        }
        
        return produceToken(TokenizerState::Init, tokens, std::move(token));
    }
}}
