#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    template<class ConstructionPolicy>
    class ReadAttributeNameState : public ParserStateInterface<ConstructionPolicy>
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack&, TokenStack&, ConstructionPolicy&) override
        {
            const auto& token = handle->token();

            if(token.type() == lexer::TokenType::equal)
            {
                return ParserState::ReadAttributeEqual;
            }
            
            throw dot_pp::SyntaxError("Unexpected token encountered, expected '=', found '" + token.to_string() + "'", *handle);
        }
    };
}}}
