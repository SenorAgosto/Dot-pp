#pragma once 
#include <Dot++/parser/TokenStack.hpp>

namespace dot_pp { namespace parser {

    class ParserStateInterface
    {
    public:
        virtual ~ParserStateInterface(){}
        virtual void consume(const lexer::Token& token, TokenStack& stack) = 0;
    };
}}
