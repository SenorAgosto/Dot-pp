#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    TokenizerState produceToken(const TokenizerState state, std::deque<TokenInfo>& tokens, Token& token, FileInfo& info)
    {
        info.advanceBy(token);
        
        if(!token.empty())
        {
            tokens.emplace_back(token, info);
        }
        
        token.clear();
        info.start() = info.end();
        
        return state;
    }
    
    TokenizerState produceToken(const TokenizerState state, std::deque<TokenInfo>& tokens, Token& token, FileInfo& info, Token&& nextToken)
    {
        info.advanceBy(token);
        
        if(!token.empty())
        {
            tokens.emplace_back(token, info);
        }
        
        token.clear();
        info.start() = info.end();

        info.advanceBy(nextToken);
        
        if(!nextToken.empty())
        {
            tokens.emplace_back(nextToken, info);
        }
                
        info.start() = info.end();
        return state;
    }
}}
