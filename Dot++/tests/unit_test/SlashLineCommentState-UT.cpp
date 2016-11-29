#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include <Dot++/states/SlashLineCommentState.hpp>
#include <Dot++/Token.hpp>
#include <Dot++/TokenInfo.hpp>
#include <Dot++/TokenizerState.hpp>

#include <deque>

namespace {
    
    struct SlashLineCommentStateFixture
    {
        SlashLineCommentStateFixture()
            : info("test.dot")
        {
        }
        
        dot_pp::FileInfo info;
        dot_pp::Token token;
        std::deque<dot_pp::TokenInfo> tokens;
        dot_pp::states::SlashLineCommentState state;
    };
    
    TEST_FIXTURE(SlashLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(SlashLineCommentStateFixture, verifyNewLineProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('a', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('b', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('c', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\n', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(SlashLineCommentStateFixture, verifyLineEscapeMovesUsToMultiLineEscape)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('a', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('b', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('c', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineEscape, state.consume('\\', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(0U, tokens.size());
        CHECK(info.empty()); // token not yet generated, empty
    }
}

