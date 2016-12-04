#include <Dot++/parser/states/GraphKeywordState.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    ParserState GraphKeywordState::consume(const TokenInfoHandle& handle, TokenStack& stack)
    {
        const auto& token = handle->token();
        
        if(token.type() == lexer::TokenType::string)
        {
            stack.push(handle);
            return ParserState::GraphName;
        }
        
        if(token.type() == lexer::TokenType::l_paren)
        {
            return ParserState::BeginGraph;
        }
        
        throw dot_pp::SyntaxError("Unexpected token after keyword 'graph' or 'digraph', expected graph name (string) or '{'.", *handle);
    }
}}}
