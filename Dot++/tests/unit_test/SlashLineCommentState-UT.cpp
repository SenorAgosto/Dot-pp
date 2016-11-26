#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include <Dot++/states/SlashLineCommentState.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/Token.hpp>

#include <deque>

namespace {
    
    struct SlashLineCommentStateFixture
    {
        SlashLineCommentStateFixture()
            : info("test.dot")
            , token(info)
        {
        }
        
        dot_pp::FileInfo info;
        dot_pp::Token token;
        std::deque<dot_pp::Token> tokens;
        dot_pp::states::SlashLineCommentState state;
    };
    
    TEST_FIXTURE(SlashLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(SlashLineCommentStateFixture, verifyNewLineProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('a', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('b', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('c', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\n', token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("abc", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].type());
    }
    
    TEST_FIXTURE(SlashLineCommentStateFixture, verifyLineEscapeMovesUsToMultiLineEscape)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('a', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('b', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('c', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineEscape, state.consume('\\', token, tokens));
        
        REQUIRE CHECK_EQUAL(0U, tokens.size());
    }
}

