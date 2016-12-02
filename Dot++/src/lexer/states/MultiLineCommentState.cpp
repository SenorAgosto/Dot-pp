#include <Dot++/lexer/states/MultiLineCommentState.hpp>

#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace lexer { namespace states {
    
    TokenizerState MultiLineCommentState::consume(const char c, FileInfo&, Token& token, std::deque<TokenInfo>&) const
    {
        if(c == '*')
        {
            return TokenizerState::EndMultiLineComment;
        }
        
        token.append(c);
        return TokenizerState::MultiLineComment;
    }
}}}
