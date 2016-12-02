#pragma once 
#include <Dot++/lexer/TokenInfo.hpp>
#include <deque>

namespace dot_pp { namespace parser {

    using TokenInfoHandle = std::deque<lexer::TokenInfo>::const_iterator;
}}
