#include "./ProduceToken.hpp"

namespace dot_pp {
    
    TokenizerState produceToken(const TokenizerState state, std::deque<Token>& tokens, Token&& token)
    {
        tokens.emplace_back(std::move(token));
        return state;
    }
}
