#include <Dot++/states/BeginSlashLineCommentState.hpp>

#include <Dot++/FileInfo.hpp>
#include <Dot++/Token.hpp>
#include <Dot++/TokenInfo.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    TokenizerState BeginSlashLineCommentState::consume(const char c, FileInfo& info, Token& token, std::deque<TokenInfo>& tokens) const
    {
        if(c == '/')
        {
            return produceToken(TokenizerState::SlashLineComment, tokens, token, info);
        }
        
        if(c == '*')
        {
            return produceToken(TokenizerState::MultiLineComment, tokens, token, info);
        }
        
        return produceToken(TokenizerState::Init, tokens, token, info);
    }
}}
