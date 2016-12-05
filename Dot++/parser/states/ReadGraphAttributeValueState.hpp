#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    template<class ConstructionPolicy>
    class ReadGraphAttributeValueState : public ParserStateInterface<ConstructionPolicy>
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack&, ConstructionPolicy&) override
        {
            const auto& token = handle->token();
            
            if(token.type() == lexer::TokenType::end_statement)
            {
                return ParserState::BeginGraph;
            }
            
            throw dot_pp::SyntaxError("Unexpected token encountered, expected ';', found '" + token.to_string() + "'", *handle);
        }
    };
}}}
