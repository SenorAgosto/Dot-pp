#include <Dot++/lexer/states/StringLiteralEscapeState.hpp>

#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace lexer { namespace states {
    
    TokenizerState StringLiteralEscapeState::consume(const char c, FileInfo&, Token& token, std::deque<TokenInfo>&) const
    {
        if(c == '"')
        {
            token.append('"');
            return TokenizerState::StringLiteral;
        }
        
        // This is really a placeholder for future use, this state can be
        // used to validate acceptable escape characters, e.g. \t \a
        token.append(c);
        return TokenizerState::StringLiteral;
    }
}}}
