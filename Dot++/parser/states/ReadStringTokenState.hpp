#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    template<class ConstructionPolicy>
    class ReadStringTokenState : public ParserStateInterface<ConstructionPolicy>
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack& stack, TokenStack& attributes, ConstructionPolicy& constructor) override
        {
            const auto& token = handle->token();
        
            if((token.type() == lexer::TokenType::edge) || (token.type() == lexer::TokenType::directed_edge))
            {
                const auto vertexName = stack.top();
                const auto vertexNameToken = vertexName->token();
                
                constructor.createVertex(vertexNameToken.to_string());
                
                return ParserState::ReadEdgeToken;
            }
        
            if(token.type() == lexer::TokenType::equal)
            {
                // migrate stack top to attribute stack since we now
                // know it's an attribute name.
                attributes.push(stack.top());
                stack.pop();
                
                return ParserState::ReadGraphAttributeEqual;
            }
        
            if(token.type() == lexer::TokenType::l_bracket)
            {
                return ParserState::ReadLeftBracketVertexAttribute;
            }
            
            throw dot_pp::SyntaxError("Unexpected token encountered, expected '--', '->', '=', or '[', found '" + token.to_string() + "'", *handle);
        }
    };
}}}
