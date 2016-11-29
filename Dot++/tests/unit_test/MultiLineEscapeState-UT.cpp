#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include <Dot++/states/MultiLineEscapeState.hpp>
#include <Dot++/Token.hpp>
#include <Dot++/TokenInfo.hpp>
#include <Dot++/TokenizerState.hpp>

#include <deque>

namespace {
    
    struct MultiLineEscapeStateFixture
    {
        MultiLineEscapeStateFixture()
            : info("test.dot")
            , token("abc", dot_pp::TokenType::string)
        {
        }
        
        dot_pp::FileInfo info;
        dot_pp::Token token;
        std::deque<dot_pp::TokenInfo> tokens;
        dot_pp::states::MultiLineEscapeState state;
    };
    
    TEST_FIXTURE(MultiLineEscapeStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(MultiLineEscapeStateFixture, verifyNewlineMovesBackToLineComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('\n', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL("abc", token.to_string());
        CHECK_EQUAL(dot_pp::TokenType::multiline_comment, token.type());
        CHECK(info.empty());    // token not yet produced, empty.
    }

    TEST_FIXTURE(MultiLineEscapeStateFixture, verifyNonNewLineIsError)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('o', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL("abc", token.to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, token.type());
        CHECK(info.empty());    // token not yet produced, empty.
    }
}

