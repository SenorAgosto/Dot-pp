#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include "Dot++/src/states/ProduceToken.hpp"
#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/TokenInfo.hpp>
#include <Dot++/TokenType.hpp>

#include <deque> 

namespace {
    
    struct ProduceTokenFixture
    {
        ProduceTokenFixture()
            : info("test.dot")
            , token("abcdefg", dot_pp::TokenType::string)
            , token2("abc\nabc", dot_pp::TokenType::multiline_comment)
        {
        }
        
        dot_pp::FileInfo info;
        dot_pp::Token token;
        dot_pp::Token token2;
        std::deque<dot_pp::TokenInfo> tokens;
    };
    
    TEST_FIXTURE(ProduceTokenFixture, verifyProduceTokenWithOneArgument)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(dot_pp::TokenizerState::Init, dot_pp::states::produceToken(dot_pp::TokenizerState::Init, tokens, token, info));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abcdefg", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(8U, tokens[0].fileInfo().end().column());
        
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, dot_pp::states::produceToken(dot_pp::TokenizerState::Init, tokens, token2, info, dot_pp::Token()));

        REQUIRE CHECK_EQUAL(2U, tokens.size());
        
        CHECK_EQUAL("abc\nabc", tokens[1].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::multiline_comment, tokens[1].token().type());
        CHECK_EQUAL(1U, tokens[1].fileInfo().start().line());
        CHECK_EQUAL(8U, tokens[1].fileInfo().start().column());
        CHECK_EQUAL(2U, tokens[1].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[1].fileInfo().end().column());
    }
}
