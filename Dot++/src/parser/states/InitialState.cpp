#include <Dot++/parser/states/InitialState.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    ParserState InitialState::consume(const TokenInfoHandle& handle, TokenStack& stack)
    {
        const auto& token = handle->token();
        
        if((token.type() == lexer::TokenType::comment) || (token.type() == lexer::TokenType::multiline_comment))
        {
            return ParserState::Init;
        }
        
        if(token.type() == lexer::TokenType::keyword)
        {
            const auto& value = token.to_string();
            if((value == "graph") || (value == "digraph"))
            {
                stack.push(handle);
                return ParserState::GraphKeyword;
            }
            
            throw dot_pp::SyntaxError("Unknown keyword, expected 'graph' or 'digraph'", *handle);
        }
        
        throw dot_pp::SyntaxError("Expected keyword 'graph' or 'digraph'", *handle);
    }
}}}
