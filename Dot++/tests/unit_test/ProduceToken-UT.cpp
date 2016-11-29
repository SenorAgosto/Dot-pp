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
        
        CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL(1U, info.start().line());
        CHECK_EQUAL(1U, info.start().column());
        CHECK_EQUAL(1U, info.end().line());
        CHECK_EQUAL(8U, info.end().column());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, dot_pp::states::produceToken(dot_pp::TokenizerState::Init, tokens, token2, info, dot_pp::Token()));

        CHECK_EQUAL(3U, tokens.size());
        CHECK_EQUAL(1U, info.start().line());
        CHECK_EQUAL(1U, info.start().column());
        CHECK_EQUAL(2U, info.end().line());
        CHECK_EQUAL(4U, info.end().column());
    }
}
