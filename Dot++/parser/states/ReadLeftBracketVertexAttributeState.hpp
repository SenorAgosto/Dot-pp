#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    template<class ConstructionPolicy>
    class ReadLeftBracketVertexAttributeState : public ParserStateInterface<ConstructionPolicy>
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack& stack, TokenStack&, ConstructionPolicy&) override
        {
            const auto& token = handle->token();
        
            if(token.type() == lexer::TokenType::string)
            {
                stack.push(handle);
                return ParserState::ReadVertexAttributeName;
            }
            
            if(token.type() == lexer::TokenType::r_bracket)
            {
                return ParserState::ReadGraphAttributeValue;
            }

            throw dot_pp::SyntaxError("Unexpected token found, expected ']' or '<string>', found '" + token.to_string() + "'", *handle);
        }
    };
}}}
