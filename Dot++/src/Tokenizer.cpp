#include <Dot++/Tokenizer.hpp>
#include <Dot++/TokenizerStateInterface.hpp>

namespace dot_pp {
    
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
}
