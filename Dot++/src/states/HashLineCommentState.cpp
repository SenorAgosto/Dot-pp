#include <Dot++/states/HashLineCommentState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

namespace dot_pp {
    
    TokenizerState HashLineCommentState::consume(const char c, Token& token) const
    {
        if(c == '\n')
        {
            token.type(TokenType::comment);
            token.produce();
            
            return TokenizerState::Init;
        }

        // ignore carriage returns
        if(c == '\r')
        {
            return TokenizerState::HashLineComment;
        }

        token.append(c);
        return TokenizerState::HashLineComment;
    }
}
