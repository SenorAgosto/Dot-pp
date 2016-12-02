#include "./platform/UnitTestSupport.hpp"

#include <Dot++/lexer/FileInfo.hpp>
#include <Dot++/lexer/states/MultiLineEscapeState.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include <deque>

namespace {
    
    using namespace dot_pp::lexer;
    
    struct MultiLineEscapeStateFixture
    {
        MultiLineEscapeStateFixture()
            : info("test.dot")
            , token("abc", TokenType::string)
        {
        }
        
        FileInfo info;
        Token token;
        std::deque<TokenInfo> tokens;
        states::MultiLineEscapeState state;
    };
    
    TEST_FIXTURE(MultiLineEscapeStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(MultiLineEscapeStateFixture, verifyNewlineMovesBackToLineComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::SlashLineComment, state.consume('\n', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL("abc\n", token.to_string());
        CHECK_EQUAL(TokenType::multiline_comment, token.type());
        CHECK(info.empty());    // token not yet produced, empty.
    }

    TEST_FIXTURE(MultiLineEscapeStateFixture, verifyNonNewLineIsError)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::Error, state.consume('o', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL("abc", token.to_string());
        CHECK_EQUAL(TokenType::string, token.type());
        CHECK(info.empty());    // token not yet produced, empty.
    }
}

