#include "./ProduceToken.hpp"

namespace dot_pp { namespace states {
    
    namespace {
        inline
        bool isDirectedEdge(const Token& token)
        {
            return token.to_string() == "->";
        }
        
        inline
        bool isEdge(const Token& token)
        {
            return token.to_string() == "--";
        }
        
        inline
        bool isKeyword(const Token& token)
        {
            return token.to_string() == "digraph" || token.to_string() == "graph";
        }
        
        inline
        void adjustTokenType(Token& token)
        {
            if(isDirectedEdge(token))
            {
                token.type(TokenType::directed_edge);
            }
            else if(isEdge(token))
            {
                token.type(TokenType::edge);
            }
            else if(isKeyword(token))
            {
                token.type(TokenType::keyword);
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
