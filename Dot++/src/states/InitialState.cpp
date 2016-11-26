#include <Dot++/states/InitialState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"
#include <utility>

namespace dot_pp { namespace states {
    
    TokenizerState InitialState::consume(const char c, Token& token, std::deque<Token>& tokens) const
    {
        const auto info = token.info();
        
        switch(c)
        {
        case '"':   return produceToken(TokenizerState::StringLiteral, tokens, std::move(token));
        case '[':   return produceToken(TokenizerState::Init, tokens, std::move(token), Token(info, "[", TokenType::l_bracket));
        case ']':   return produceToken(TokenizerState::Init, tokens, std::move(token), Token(info, "]", TokenType::r_bracket));
        case '=':   return produceToken(TokenizerState::Init, tokens, std::move(token), Token(info, "=", TokenType::equal));
        case '#':   return produceToken(TokenizerState::HashLineComment, tokens, std::move(token));
        case '/':   return produceToken(TokenizerState::SlashLineComment, tokens, std::move(token));
        case ' ':   return produceToken(TokenizerState::Init, tokens, std::move(token));
        case '\t':  return produceToken(TokenizerState::Init, tokens, std::move(token));
        case '\n':  return produceToken(TokenizerState::Init, tokens, std::move(token));
        case '\r':  return produceToken(TokenizerState::Init, tokens, std::move(token));

        default: break;
        };
        
        token.append(c);
        return TokenizerState::Init;
    }
}}
