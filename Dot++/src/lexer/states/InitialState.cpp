#include <Dot++/lexer/states/InitialState.hpp>

#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include "./ProduceToken.hpp"
#include <utility>

namespace dot_pp { namespace lexer { namespace states {
    
    TokenizerState InitialState::consume(const char c, FileInfo& info, Token& token, std::deque<TokenInfo>& tokens) const
    {
        switch(c)
        {
        case '"':   return produceToken(TokenizerState::StringLiteral, tokens, token, info);
        case ';':   return produceToken(TokenizerState::Init, tokens, token, info, Token(";", TokenType::end_statement));
        case '[':   return produceToken(TokenizerState::Init, tokens, token, info, Token("[", TokenType::l_bracket));
        case ']':   return produceToken(TokenizerState::Init, tokens, token, info, Token("]", TokenType::r_bracket));
        case '=':   return produceToken(TokenizerState::Init, tokens, token, info, Token("=", TokenType::equal));
        case '{':   return produceToken(TokenizerState::Init, tokens, token, info, Token("{", TokenType::l_paren));
        case '}':   return produceToken(TokenizerState::Init, tokens, token, info, Token("}", TokenType::r_paren));
        case '#':   return produceToken(TokenizerState::HashLineComment, tokens, token, info);
        case '/':   return produceToken(TokenizerState::SlashLineComment, tokens, token, info);
        case ' ':   return produceToken(TokenizerState::Init, tokens, token, info);
        case '\t':  return produceToken(TokenizerState::Init, tokens, token, info);
        case '\n':  return produceToken(TokenizerState::Init, tokens, token, info);
        case '\r':  return produceToken(TokenizerState::Init, tokens, token, info);

        default: break;
        };
        
        token.append(c);
        return TokenizerState::Init;
    }
}}}
