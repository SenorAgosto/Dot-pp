#include <Dot++/states/InitialState.hpp>

#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include "./ProduceToken.hpp"
#include <utility>

namespace dot_pp { namespace states {
    
    TokenizerState InitialState::consume(const char c, FileInfo& info, Token& token, std::deque<TokenInfo>& tokens) const
    {
        switch(c)
        {
        case '"':   return produceToken(TokenizerState::StringLiteral, info, tokens, token);
        case '[':   return produceToken(TokenizerState::Init, info, tokens, token, Token("[", TokenType::l_bracket));
        case ']':   return produceToken(TokenizerState::Init, info, tokens, token, Token("]", TokenType::r_bracket));
        case '=':   return produceToken(TokenizerState::Init, info, tokens, token, Token("=", TokenType::equal));
        case '#':   return produceToken(TokenizerState::HashLineComment, info, tokens, token);
        case '/':   return produceToken(TokenizerState::SlashLineComment, info, tokens, token);
        case ' ':   return produceToken(TokenizerState::Init, info, tokens, token);
        case '\t':  return produceToken(TokenizerState::Init, info, tokens, token);
        case '\n':  return produceToken(TokenizerState::Init, info, tokens, token);
        case '\r':  return produceToken(TokenizerState::Init, info, tokens, token);

        default: break;
        };
        
        token.append(c);
        return TokenizerState::Init;
    }
}}
