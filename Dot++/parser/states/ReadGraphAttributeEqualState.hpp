#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    template<class ConstructionPolicy>
    class ReadGraphAttributeEqualState : public ParserStateInterface<ConstructionPolicy>
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack&, TokenStack& attributes, ConstructionPolicy& constructor) override
        {
            const auto& token = handle->token();
        
            if((token.type() == lexer::TokenType::string) || (token.type() == lexer::TokenType::string_literal))
            {
                const auto attribute = attributes.top();
                const auto attributeToken = attribute->token();
                attributes.pop();
                
                constructor.applyGraphAttribute(attributeToken.to_string(), token.to_string());
                
                return ParserState::ReadGraphAttributeValue;
            }
            
            throw dot_pp::SyntaxError("Unexpected token encountered, expected 'string' or 'string_literal', found '" + token.to_string() + "'", *handle);
        }
    };
}}}
