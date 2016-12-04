#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    template<class ConstructionPolicy>
    class GraphKeywordState : public ParserStateInterface<ConstructionPolicy>
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack& stack, ConstructionPolicy& constructor) override
        {
            const auto& token = handle->token();
            
            if(token.type() == lexer::TokenType::string)
            {
                stack.push(handle);
                return ParserState::GraphName;
            }
            
            if(token.type() == lexer::TokenType::l_paren)
            {
                const auto top = stack.top();
                stack.pop();
                
                const auto& topToken = top->token();
                
                if(topToken.to_string() == "graph")
                {
                    constructor.createGraph("");
                }
                else if(topToken.to_string() == "digraph")
                {
                    constructor.createDigraph("");
                }
                else
                {
                    throw dot_pp::SyntaxError("Unexpected keyword value, expected 'graph' or 'digraph' found '" + topToken.to_string() + "'", *handle);
                }
                
                return ParserState::BeginGraph;
            }
            
            throw dot_pp::SyntaxError("Unexpected token after keyword 'graph' or 'digraph', expected graph name (string) or '{'.", *handle);
        }
    };
}}}
