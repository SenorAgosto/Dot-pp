#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    TokenizerState produceToken(const TokenizerState state, std::deque<TokenInfo>& tokens, Token& token, FileInfo& info)
    {
        info.advanceBy(token);
        tokens.emplace_back(token, info);
        token.clear();
        
        return state;
    }
    
    TokenizerState produceToken(const TokenizerState state, std::deque<TokenInfo>& tokens, Token& token, FileInfo& info, Token&& nextToken)
    {
        info.advanceBy(token);
        tokens.emplace_back(token, info);
        token.clear();
        
        info.advanceBy(nextToken);
        tokens.emplace_back(nextToken, info);
        
        return state;
    }
}}
