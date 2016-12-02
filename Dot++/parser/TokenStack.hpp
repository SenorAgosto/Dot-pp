#pragma once

#include <Dot++/lexer/TokenInfo.hpp>
#include <deque>
#include <stack>

namespace dot_pp { namespace parser {

    using TokenStack = std::stack<std::deque<lexer::TokenInfo>::const_iterator>;
}}
