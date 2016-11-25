#pragma once
#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include <deque>
#include <utility>

namespace dot_pp {

    TokenizerState produceToken(const TokenizerState state, std::deque<Token>& tokens, Token&& token);
    
    // allow multiple tokens to be added to @tokens
    // e.g. produceToken(TokenizerState::Init, tokens, token1, Token("blah", TokenType::string));
    template<typename... TokenPack>
    TokenizerState produceToken(const TokenizerState state, std::deque<Token>& tokens, Token&& token, TokenPack&&... tokenPack)
    {
        produceToken(state, tokens, std::move(token));
        return produceToken(state, tokens, std::forward<TokenPack>(tokenPack)...);
    }
}
