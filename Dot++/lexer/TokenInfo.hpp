#pragma once

#include <Dot++/lexer/FileInfo.hpp>
#include <Dot++/lexer/Token.hpp>

namespace dot_pp { namespace lexer {
    
    class TokenInfo
    {
    public:
        TokenInfo(const Token& token, const FileInfo& info);
        
        const FileInfo& fileInfo() const { return fileInfo_; }
        FileInfo& fileInfo() { return fileInfo_; }

        void token(const Token& token) { token_ = token; }
        const Token& token() const { return token_; }
        Token& token() { return token_; }

    private:
        FileInfo fileInfo_;
        Token token_;
    };
}}
