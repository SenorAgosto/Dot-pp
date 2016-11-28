#include <Dot++/states/MultiLineCommentState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    TokenizerState MultiLineCommentState::consume(const char c, FileInfo&, Token& token, std::deque<TokenInfo>&) const
    {
        if(c == '*')
        {
            return TokenizerState::EndMultiLineComment;
        }
        
        token.append(c);
        return TokenizerState::MultiLineComment;
    }
}}
