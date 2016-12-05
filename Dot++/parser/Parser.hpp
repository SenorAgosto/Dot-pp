#pragma once
#include <Dot++/parser/ParserStatesPack.hpp>
#include <Dot++/parser/TokenInfoHandle.hpp>
#include <Dot++/parser/TokenStack.hpp>

namespace dot_pp { namespace parser {

    template<class ConstructionPolicy>
    class Parser
    {
    public:
        Parser(ConstructionPolicy& constructor);
        
        void consume(const TokenInfoHandle& token);
        
    private:
        ConstructionPolicy& constructor_;
        TokenStack stack_;
        
        ParserStatesPack<ConstructionPolicy> states_;
        ParserState state_;
    };
    
    template<class ConstructionPolicy>
    Parser<ConstructionPolicy>::Parser(ConstructionPolicy& constructor)
        : constructor_(constructor)
    {
    }
    
    template<class ConstructionPolicy>
    inline
    void Parser<ConstructionPolicy>::consume(const TokenInfoHandle& token)
    {
        state_ = states_.consume(state_, token, stack_, constructor_);
    }
}}
