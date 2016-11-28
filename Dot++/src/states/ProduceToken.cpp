#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    TokenizerState produceToken(const TokenizerState state, std::deque<TokenInfo>& tokens, Token& token, FileInfo& info)
    {
        info.end().incrementColumn();
        tokens.emplace_back(token, info);
        
        token.clear();
        return state;
    }
    
    TokenizerState produceToken(const TokenizerState state, std::deque<TokenInfo>& tokens, Token& token, FileInfo& info, Token&& nextToken, FileInfo&& nextInfo)
    {
        tokens.emplace_back(token, info);
        token.clear();
        
        tokens.emplace_back(nextToken, nextInfo);
        
        return state;
    }
}}
