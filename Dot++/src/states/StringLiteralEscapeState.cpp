#include <Dot++/states/StringLiteralEscapeState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
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
}}
