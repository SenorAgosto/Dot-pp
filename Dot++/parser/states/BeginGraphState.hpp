#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    template<class ConstructionPolicy>
    class BeginGraphState : public ParserStateInterface<ConstructionPolicy>
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack& stack, ConstructionPolicy& constructor) override
        {
            const auto& token = handle->token();

            switch(token.type())
            {
            case lexer::TokenType::string:              stack.push(handle);     return ParserState::ReadStringToken;
            case lexer::TokenType::l_paren:                                     return ParserState::IgnoreSubgraphs;
            case lexer::TokenType::r_paren:             constructor.finalize(); return ParserState::Init;
            case lexer::TokenType::comment:                                     return ParserState::BeginGraph;
            case lexer::TokenType::multiline_comment:                           return ParserState::BeginGraph;
            
            default: break;
            };
            
            throw dot_pp::SyntaxError("Unexpected token, expected 'string', '{', or '}' token, found '" + token.to_string() + "'", *handle);
        }
    };
}}}
