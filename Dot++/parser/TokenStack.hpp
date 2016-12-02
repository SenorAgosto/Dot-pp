#pragma once

#include <Dot++/TokenInfo.hpp>
#include <deque>
#include <stack>

namespace dot_pp { namespace parser {

    using TokenStack = std::stack<std::deque<lexer::TokenInfo>::const_iterator>;
}}
