#pragma once

#include <Dot++/FileInfo.hpp>
#include <Dot++/Token.hpp>

namespace dot_pp {
    
    class TokenInfo
    {
    public:
        TokenInfo(const Token& token, const FileInfo& info);
        
        void fileInfo(const FileInfo& info) { fileInfo_ = info; }
        const FileInfo& fileInfo() const { return fileInfo_; }
        FileInfo& fileInfo() { return fileInfo_; }

        void token(const Token& token) { token_ = token; }
        const Token& token() const { return token_; }
        Token& token() { return token_; }

    private:
        FileInfo fileInfo_;
        Token token_;
    };
}
