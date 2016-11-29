#pragma once

#include <Dot++/FileInfo.hpp>
#include <Dot++/Token.hpp>
#include <Dot++/TokenInfo.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/TokenizerStatesPack.hpp>

#include <deque>
#include <memory>
#include <string>

namespace dot_pp {

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
}
