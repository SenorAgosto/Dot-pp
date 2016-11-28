#pragma once
#include <Dot++/TokenizerStateInterface.hpp>

namespace dot_pp {
    class FileInfo;
    enum class TokenizerState;
    class Token;
}

namespace dot_pp { namespace states {
    
    class BeginSlashLineCommentState : public TokenizerStateInterface
    {
    public:
        TokenizerState consume(const char c, FileInfo& info, Token& token, std::deque<TokenInfo>& tokens) const override;
    };
}}
