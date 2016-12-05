#pragma once 
#include <Dot++/lexer/Tokenizer.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/parser/Parser.hpp>

#include <deque>
#include <istream>

namespace dot_pp {
    
    template<class ConstructionPolicy>
    class Parser
    {
    public:
        Parser(ConstructionPolicy& constructor);
        void parse(std::istream& stream, const std::string& filename, ConstructionPolicy& policy);
    
    private:
        std::deque<lexer::TokenInfo> tokenize(std::istream& stream, const std::string& filename);
        void parseTokens(const std::deque<lexer::TokenInfo>& tokens);
        
    private:
        ConstructionPolicy& constructor_;
    };
    
    
    template<class ConstructionPolicy>
    Parser<ConstructionPolicy>::Parser(ConstructionPolicy& constructor)
        : constructor_(constructor)
    {
    }
    
    template<class ConstructionPolicy>
    void Parser<ConstructionPolicy>::parse(std::istream& stream, const std::string& filename, ConstructionPolicy& /*policy*/)
    {
        auto tokens = tokenize(stream, filename);
        parseTokens(tokens);
    }
    
    template<class ConstructionPolicy>
    std::deque<lexer::TokenInfo> Parser<ConstructionPolicy>::tokenize(std::istream& stream, const std::string& filename)
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
    
    template<class ConstructionPolicy>
    void Parser<ConstructionPolicy>::parseTokens(const std::deque<lexer::TokenInfo>& tokens)
    {
        parser::Parser<ConstructionPolicy> parser(constructor_);
        
        for(auto handle = tokens.cbegin(), end = tokens.cend(); handle != end; ++handle)
        {
            const auto& token = handle->token();
            if((token.type() == lexer::TokenType::comment) || (token.type() == lexer::TokenType::multiline_comment))
            {
                continue;
            }
            
            parser.consume(handle);
        }
    }
}
