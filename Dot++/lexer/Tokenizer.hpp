#pragma once

#include <Dot++/lexer/FileInfo.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/lexer/TokenizerState.hpp>
#include <Dot++/lexer/TokenizerStatesPack.hpp>

#include <deque>
#include <memory>
#include <string>

namespace dot_pp { namespace lexer {

    class Tokenizer
    {
    public:
        Tokenizer(const std::string& filename);
        void consume(const char c, std::deque<TokenInfo>& tokens);
        
    private:
        const std::string filename_;
        TokenizerStatesPack states_;

        FileInfo fileInfo_;
        Token token_;
        TokenizerState state_;
    };
}}
