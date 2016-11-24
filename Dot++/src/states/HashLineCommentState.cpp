#include <Dot++/states/HashLineCommentState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

namespace dot_pp {
    
    TokenizerState HashLineCommentState::consume(const char c, Token& token) const
    {
        if(c == '\n')
        {
            return TokenizerState::Init;
        }
        
        token.append(c);
        return TokenizerState::HashLineComment;
    }
}
