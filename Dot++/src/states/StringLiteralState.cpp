#include <Dot++/states/StringLiteralState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    TokenizerState StringLiteralState::consume(const char c, FileInfo& info, Token& token, std::deque<TokenInfo>& tokens) const
    {
        if(c == '"')
        {
            token.type(TokenType::string_literal);
            return produceToken(TokenizerState::Init, info, tokens, token);
        }
        
        if(c == '\\')
        {
            return TokenizerState::StringLiteralEscape;
        }
        
        token.append(c);
        return TokenizerState::StringLiteral;
    }
}}
