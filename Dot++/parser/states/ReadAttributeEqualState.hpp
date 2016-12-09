#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

#include <vector>

namespace dot_pp { namespace parser { namespace states {

    template<class ConstructionPolicy>
    class ReadAttributeEqualState : public ParserStateInterface<ConstructionPolicy>
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

                std::vector<TokenInfoHandle> tokens;
                while(!stack.empty())
                {
                    tokens.push_back(stack.top());
                    stack.pop();
                }
                
                for(std::size_t v2 = 0, v1 = 1, end = tokens.size(); v1 < end; ++v2, ++v1)
                {
                    const auto v1Token = tokens[v1]->token();
                    const auto v2Token = tokens[v2]->token();
                    
                    constructor.applyEdgeAttribute(v1Token.to_string(), v2Token.to_string(), attributeToken.to_string(), token.to_string());
                }

                for(auto iter = tokens.crbegin(), end = tokens.crend(); iter != end; ++iter)
                {
                    stack.push(*iter);
                }
                
                return ParserState::ReadLeftBracket;
            }
            
            throw dot_pp::SyntaxError("Unexpected token encountered, expected <string> or <string_literal>, found '" + token.to_string() + "'", *handle);
        }
    };
}}}
