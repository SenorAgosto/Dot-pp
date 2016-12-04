#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    template<class ConstructionPolicy>
    class GraphNameState : public ParserStateInterface<ConstructionPolicy>
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack& stack, ConstructionPolicy& constructor) override
        {
            const auto& token = handle->token();
            
            if((token.type() == lexer::TokenType::comment) || (token.type() == lexer::TokenType::multiline_comment))
            {
                return ParserState::GraphName;
            }
            
            if(token.type() == lexer::TokenType::l_paren)
            {
                const auto graphName = stack.top();
                const auto graphNameToken = graphName->token();
                stack.pop();
                
                const auto graphKeyword = stack.top();
                const auto graphKeywordToken = graphKeyword->token();
                stack.pop();
                
                if(graphKeywordToken.to_string() == "graph")
                {
                    constructor.createGraph(graphNameToken.to_string());
                }
                else if(graphKeywordToken.to_string() == "digraph")
                {
                    constructor.createDigraph(graphNameToken.to_string());
                }
                else
                {
                    throw dot_pp::SyntaxError("Unexpected keyword value, expected 'graph' or 'digraph' found '" + graphKeywordToken.to_string() + "'", *handle);
                }
                
                return ParserState::BeginGraph;
            }

            throw dot_pp::SyntaxError("Unexpected token after graph name, expected '{', found '" + token.to_string() + "'", *handle);
        }
    };
}}}
