#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    template<class ConstructionPolicy>
    class ReadVertexAttributeEqualState : public ParserStateInterface<ConstructionPolicy>
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack& stack, TokenStack& attributes, ConstructionPolicy& constructor) override
        {
            const auto& token = handle->token();
        
            if((token.type() == lexer::TokenType::string) || (token.type() == lexer::TokenType::string_literal))
            {
                const auto attribute = attributes.top();
                const auto attributeToken = attribute->token();
                attributes.pop();
                
                const auto vertex = stack.top();
                const auto vertexToken = vertex->token();
                const auto vertexName = vertexToken.to_string();
                
                if(vertexName == "node")
                {
                    constructor.applyDefaultVertexAttribute(attributeToken.to_string(), token.to_string());
                    return ParserState::ReadLeftBracketVertexAttribute;
                }
                
                if(vertexName == "edge")
                {
                    constructor.applyDefaultEdgeAttribute(attributeToken.to_string(), token.to_string());
                    return ParserState::ReadLeftBracketVertexAttribute;
                }
                
                constructor.applyVertexAttribute(vertexToken.to_string(), attributeToken.to_string(), token.to_string());
                return ParserState::ReadLeftBracketVertexAttribute;
            }
            
            throw dot_pp::SyntaxError("Unexpected token found, expected '<string>' or '<string_literal>', found '" + token.to_string() + "'", *handle);
        }
    };
}}}
