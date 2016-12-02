#include <Dot++/Exceptions.hpp>
#include <sstream>

namespace dot_pp {
    
    namespace {
        
        std::string constructError(const std::string& s, const lexer::TokenizerState state)
        {
            std::stringstream ss;
            ss << s << static_cast<int>(state);
            
            return ss.str();
        }
    }
    
    TokenizerError::TokenizerError(const std::string& reason)
        : std::runtime_error(reason)
    {
    }
    
    UnknownTokenizerState::UnknownTokenizerState(const lexer::TokenizerState state)
        : TokenizerError(constructError("Unknown Tokenizer State: ", state))
    {
    }
}
