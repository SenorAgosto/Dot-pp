#pragma once 

namespace dot_pp {
    class Token;
    enum class TokenizerState;
}

namespace dot_pp {
    
    class TokenizerStateInterface
    {
    public:
        virtual ~TokenizerStateInterface() {}
        virtual TokenizerState consume(const char c, Token& token) const = 0;
    };
}
