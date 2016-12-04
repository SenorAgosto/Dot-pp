#pragma once

#include <Dot++/parser/TokenInfoHandle.hpp>
#include <deque>
#include <stack>

namespace dot_pp { namespace parser {

    using TokenStack = std::stack<TokenInfoHandle>;
}}
