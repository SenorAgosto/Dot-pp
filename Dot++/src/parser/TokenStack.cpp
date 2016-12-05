#include <Dot++/parser/TokenStack.hpp>

namespace dot_pp { namespace parser {

    void clear(TokenStack& stack)
    {
        TokenStack s;
        stack.swap(s);
    }
}}
