#include <Dot++/lexer/Tokenizer.hpp>
#include <Dot++/lexer/TokenizerStateInterface.hpp>

namespace dot_pp { namespace lexer {
    
    Tokenizer::Tokenizer(const std::string& filename)
        : filename_(filename)
        , fileInfo_(filename)
        , state_(TokenizerState::Init)
    {
    }
    
    void Tokenizer::consume(const char c, std::deque<TokenInfo>& tokens)
    {
        state_ = states_[state_].consume(c, fileInfo_, token_, tokens);
    }
}}
