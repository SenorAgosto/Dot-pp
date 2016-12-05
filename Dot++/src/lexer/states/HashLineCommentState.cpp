#include <Dot++/lexer/states/HashLineCommentState.hpp>

#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace lexer { namespace states {
    
    TokenizerState HashLineCommentState::consume(const char c, FileInfo& info, Token& token, std::deque<TokenInfo>& tokens) const
    {
        if(c == '\n')
        {
            token.type(TokenType::comment);
            
            const auto state = produceToken(TokenizerState::Init, tokens, token, info);
            info.incrementLine();
            
            return state;
        }

        // ignore carriage returns
        if(c == '\r')
        {
            return TokenizerState::HashLineComment;
        }

        token.append(c);        
        return TokenizerState::HashLineComment;
    }
}}}
