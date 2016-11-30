#pragma once 
#include <Dot++/Tokenizer.hpp>
#include <Dot++/TokenInfo.hpp>

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
        std::deque<TokenInfo> tokenize(std::istream& stream, const std::string& filename);
        
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
    std::deque<TokenInfo> Parser<ConstructionPolicy, LoggingInterface>::tokenize(std::istream& stream, const std::string& filename)
    {
        Tokenizer tokenizer(filename);
        std::deque<TokenInfo> tokens;

        while(!stream.eof())
        {
            const char c = stream.get();
            tokenizer.consume(c, tokens);
        }
        
        return tokens;
    }
}
