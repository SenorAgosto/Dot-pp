#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    template<class ConstructionPolicy>
    class ReadAttributeEqualState : public ParserStateInterface<ConstructionPolicy>
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack& stack, TokenStack&, ConstructionPolicy& constructor) override
        {
            const auto& token = handle->token();
            
            if((token.type() == lexer::TokenType::string) || (token.type() == lexer::TokenType::string_literal))
            {
                const auto attribute = stack.top();
                const auto attributeToken = attribute->token();
                stack.pop();
                
                const auto v2 = stack.top();
                const auto v2Token = v2->token();
                stack.pop();
                
                const auto v1 = stack.top();
                const auto v1Token = v1->token();
                
                stack.push(v2);
                
                constructor.applyEdgeAttribute(v1Token.to_string(), v2Token.to_string(), attributeToken.to_string(), token.to_string());
                
                return ParserState::ReadLeftBracket;
            }
            
            throw dot_pp::SyntaxError("Unexpected token encountered, expected <string> or <string_literal>, found '" + token.to_string() + "'", *handle);
        }
    };
}}}
