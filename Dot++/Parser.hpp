#pragma once 
#include <Dot++/lexer/Tokenizer.hpp>
#include <Dot++/lexer/TokenInfo.hpp>

#include <deque>
#include <istream>

namespace dot_pp {
    
    template<class ConstructionPolicy, class LoggingInterface>
    class Parser
    {
    public:
        Parser(LoggingInterface& logHandle);
        void parse(std::istream& stream, const std::string& filename, ConstructionPolicy& policy);
    
    private:
        std::deque<lexer::TokenInfo> tokenize(std::istream& stream, const std::string& filename);
        
    private:
        LoggingInterface& log_;
    };
    
    
    template<class ConstructionPolicy, class LoggingInterface>
    Parser<ConstructionPolicy, LoggingInterface>::Parser(LoggingInterface& logHandle)
        : log_(logHandle)
    {
    }
    
    template<class ConstructionPolicy, class LoggingInterface>
    void Parser<ConstructionPolicy, LoggingInterface>::parse(std::istream& stream, const std::string& filename, ConstructionPolicy& /*policy*/)
    {
        try
        {
            auto tokens = tokenize(stream, filename);
            // TODO: iterate over tokens constructing AST
        }
        catch(const std::exception& e)
        {
            log_.error(std::string("Exception: ") + e.what());
        }
    }
    
    template<class ConstructionPolicy, class LoggingInterface>
    std::deque<lexer::TokenInfo> Parser<ConstructionPolicy, LoggingInterface>::tokenize(std::istream& stream, const std::string& filename)
    {
        lexer::Tokenizer tokenizer(filename);
        std::deque<lexer::TokenInfo> tokens;

        while(!stream.eof())
        {
            const char c = stream.get();
            tokenizer.consume(c, tokens);
        }
        
        return tokens;
    }
}
