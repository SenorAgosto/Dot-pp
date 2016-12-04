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
        
        std::string constructFileLocationString(const std::string& s, const lexer::TokenInfo& info, const std::string& error)
        {
            std::stringstream ss;
            ss  << s
                << info.fileInfo().end().line() << ":" << info.fileInfo().end().column()
                << ": " << error;
            
            return ss.str();
        }
        
        std::string constructParserStateError(const std::string& s, const parser::ParserState state)
        {
            std::stringstream ss;
            ss << s << static_cast<int>(state);
            
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
        : ParserError(constructFileLocationString("Syntax Error: ", info, error))
    {
    }
    
    UnknownParserState::UnknownParserState(const parser::ParserState state)
        : ParserError(constructParserStateError("Unknown parser state encountered: ", state))
    {
    }
}
