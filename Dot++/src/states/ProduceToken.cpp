#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    TokenizerState produceToken(const TokenizerState state, const FileInfo& info, std::deque<TokenInfo>& tokens, Token& token)
    {
        tokens.emplace_back(token, info);
        token.clear();
        
        return state;
    }
    
    TokenizerState produceToken(const TokenizerState state, const FileInfo& info, std::deque<TokenInfo>& tokens, Token& token, Token&& nextToken)
    {
        tokens.emplace_back(token, info);
        tokens.emplace_back(nextToken, info);   // TODO: info has to be adjusted to reflect nextToken
        
        token.clear();
        return state;
    }
}}
