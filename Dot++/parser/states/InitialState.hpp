#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

namespace dot_pp { namespace parser { namespace states {

    class InitialState : public ParserStateInterface
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack& stack) override;
    };
}}}
