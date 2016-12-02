#include <Dot++/lexer/states/BeginSlashLineCommentState.hpp>

#include <Dot++/lexer/FileInfo.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace lexer { namespace states {
    
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
}}}
