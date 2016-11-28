#pragma once
#include <Dot++/Token.hpp>
#include <Dot++/TokenInfo.hpp>
#include <Dot++/TokenizerState.hpp>

#include <deque>
#include <utility>

namespace dot_pp { namespace states {

    TokenizerState produceToken(const TokenizerState state, const FileInfo& info, std::deque<TokenInfo>& tokens, Token& token);
    TokenizerState produceToken(const TokenizerState state, const FileInfo& info, std::deque<TokenInfo>& tokens, Token& token, Token&& nextToken);
}}
