#pragma once
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include <deque>
#include <utility>

namespace dot_pp { namespace lexer {  namespace states {

    TokenizerState produceToken(const TokenizerState state, std::deque<TokenInfo>& tokens, Token& token, FileInfo& info);
    TokenizerState produceToken(const TokenizerState state, std::deque<TokenInfo>& tokens, Token& token, FileInfo& info, Token&& nextToken);
}}}
