#pragma once

#include <Dot++/parser/TokenInfoHandle.hpp>
#include <deque>
#include <stack>

namespace dot_pp { namespace parser {

    using TokenStack = std::stack<TokenInfoHandle>;
    
    // empty out @stack
    void clear(TokenStack& stack);
}}
