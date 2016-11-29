#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Tokenizer.hpp>
#include <deque>
#include <sstream>

namespace {
    
    struct TokenizerFixture
    {
        TokenizerFixture()
            : tokenizer("test.dot")
        {
        }
        
        dot_pp::Tokenizer tokenizer;
        std::deque<dot_pp::TokenInfo> tokens;
    };
    
    TEST_FIXTURE(TokenizerFixture, verifyInstantation)
    {
    }
    
    TEST_FIXTURE(TokenizerFixture, verifyTokenizationOfWhitespace)
    {
        std::stringstream ss;
        ss << "    \t \n\t   \t";
        
        for(const auto c : ss.str())
        {
            tokenizer.consume(c, tokens);
        }
        
        REQUIRE CHECK_EQUAL(0U, tokens.size());
    }
    
    TEST_FIXTURE(TokenizerFixture, verifyTokenizeGraph)
    {
        std::stringstream ss;
        ss  << "digraph test {" "\n"
            << "\t" "a -> b;" "\n"
            << "\t" "a -> c;" "\n"
            << "}\n";
        
        for(const auto c : ss.str())
        {
            tokenizer.consume(c, tokens);
        }
        
        REQUIRE CHECK_EQUAL(10U, tokens.size());
        
        CHECK_EQUAL("digraph", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());
        
        CHECK_EQUAL("test", tokens[1].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[1].token().type());
        
        CHECK_EQUAL("{", tokens[2].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::l_paren, tokens[2].token().type());
        
        CHECK_EQUAL("a", tokens[3].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[3].token().type());
        
        CHECK_EQUAL("->", tokens[4].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[4].token().type());

        CHECK_EQUAL("b;", tokens[5].token().to_string());                       // TODO: should just be 'b'
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[5].token().type());
        
        CHECK_EQUAL("a", tokens[6].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[6].token().type());
        
        CHECK_EQUAL("->", tokens[7].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[7].token().type());

        CHECK_EQUAL("c;", tokens[8].token().to_string());                     // TODO: should just be 'c'
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[8].token().type());

        CHECK_EQUAL("}", tokens[9].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::r_paren, tokens[9].token().type());
    }
}
