#pragma once 
#include <Dot++/TokenizerStateInterface.hpp>

namespace dot_pp {
    enum class TokenizerState;
    class Token;
}

namespace dot_pp {
    
    class HashLineCommentState : public TokenizerStateInterface
    {
    public:
        TokenizerState consume(const char c, Token& token) const override;
    };
}
