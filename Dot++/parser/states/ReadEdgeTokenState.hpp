#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    template<class ConstructionPolicy>
    class ReadEdgeTokenState : public ParserStateInterface<ConstructionPolicy>
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack& stack, TokenStack&, ConstructionPolicy& constructor) override
        {
            const auto& token = handle->token();
            
            if(token.type() == lexer::TokenType::string)
            {
                const auto vertex1 = stack.top();
                const auto vertex1Token = vertex1->token();
                
                const auto vertex2 = token.to_string();
                constructor.createVertex(vertex2);
                constructor.createEdge(vertex1Token.to_string(), vertex2);
                
                stack.push(handle);
                return ParserState::CreatedEdge;
            }
        
            throw dot_pp::SyntaxError("Unexpected token encountered, expected 'string', found '" + token.to_string() + "'", *handle);
            

        }
    };
}}}
