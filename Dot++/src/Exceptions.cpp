#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/TokenInfo.hpp>

#include <sstream>

namespace dot_pp {
    
    namespace {
        
        std::string constructError(const std::string& s, const lexer::TokenizerState state)
        {
            std::stringstream ss;
            ss << s << static_cast<int>(state);
            
            return ss.str();
        }
        
        std::string constructFileLocationString(const lexer::TokenInfo& info)
        {
            std::stringstream ss;
            ss << info.fileInfo().end().line() << ":" << info.fileInfo().end().column();
            
            return ss.str();
        }
    }

    ParserError::ParserError(const std::string& reason)
        : std::runtime_error(reason)
    {
    }
    
    TokenizerError::TokenizerError(const std::string& reason)
        : std::runtime_error(reason)
    {
    }
    
    UnknownTokenizerState::UnknownTokenizerState(const lexer::TokenizerState state)
        : TokenizerError(constructError("Unknown Tokenizer State: ", state))
    {
    }
    
    SyntaxError::SyntaxError(const std::string& error, const lexer::TokenInfo& info)
        : ParserError("Syntax Error: " + constructFileLocationString(info) + ": " + error)
    {
    }
}
