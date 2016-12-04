#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

namespace dot_pp { namespace parser { namespace states {

    class GraphKeywordState : public ParserStateInterface
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack& stack) override;
    };
}}}
