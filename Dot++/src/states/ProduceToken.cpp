#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    namespace {
        inline
        bool isDirectedArrow(const Token& token)
        {
            return token.to_string() == "->";
        }
        
        inline
        bool isUndirectedArrow(const Token& token)
        {
            return token.to_string() == "--";
        }
        
        inline
        void adjustTokenType(Token& token)
        {
            if(isDirectedArrow(token))
            {
                token.type(TokenType::arrow);
            }
            else if(isUndirectedArrow(token))
            {
                token.type(TokenType::bidirectional_arrow);
            }
        }
    }
    
    TokenizerState produceToken(const TokenizerState state, std::deque<TokenInfo>& tokens, Token& token, FileInfo& info)
    {
        info.advanceBy(token);
        
        if(!token.empty())
        {
            adjustTokenType(token);
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
            adjustTokenType(token);
            tokens.emplace_back(token, info);
        }
        
        token.clear();
        info.start() = info.end();

        info.advanceBy(nextToken);
        
        if(!nextToken.empty())
        {
            adjustTokenType(nextToken);
            tokens.emplace_back(nextToken, info);
        }
                
        info.start() = info.end();
        return state;
    }
}}
