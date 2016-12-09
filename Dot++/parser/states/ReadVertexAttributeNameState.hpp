#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    template<class ConstructionPolicy>
    class ReadVertexAttributeNameState : public ParserStateInterface<ConstructionPolicy>
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack&, ConstructionPolicy&) override
        {
            const auto& token = handle->token();
        
            if(token.type() == lexer::TokenType::equal)
            {
                return ParserState::ReadVertexAttributeEqual;
            }
            
            throw dot_pp::SyntaxError("Unexpected token found, expected '=', found '" + token.to_string() + "'", *handle);
        }
    };
}}}
