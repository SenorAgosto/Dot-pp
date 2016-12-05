#include <Dot++/lexer/states/EndMultiLineCommentState.hpp>

#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace lexer { namespace states {
    
    TokenizerState EndMultiLineCommentState::consume(const char c, FileInfo& info, Token& token, std::deque<TokenInfo>& tokens) const
    {        
        if(c == '/')
        {
            token.type(TokenType::multiline_comment);
            
            const auto state = produceToken(TokenizerState::Init, tokens, token, info);
            info.incrementColumn();
            
            return state;
        }
        
        token.append(c);
        return TokenizerState::MultiLineComment;
    }
}}}
