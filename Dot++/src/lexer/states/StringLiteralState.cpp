#include <Dot++/lexer/states/StringLiteralState.hpp>

#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace lexer { namespace states {
    
    TokenizerState StringLiteralState::consume(const char c, FileInfo& info, Token& token, std::deque<TokenInfo>& tokens) const
    {
        if(c == '"')
        {
            info.incrementColumn();
            token.type(TokenType::string_literal);
            
            return produceToken(TokenizerState::Init, tokens, token, info);
        }
        
        if(c == '\\')
        {
            info.incrementColumn();
            return TokenizerState::StringLiteralEscape;
        }
        
        token.append(c);
        return TokenizerState::StringLiteral;
    }
}}}
