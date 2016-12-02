#include "./platform/UnitTestSupport.hpp"

#include <Dot++/lexer/FileInfo.hpp>
#include <Dot++/lexer/states/SlashLineCommentState.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include <deque>

namespace {
    
    using namespace dot_pp::lexer;
    
    struct SlashLineCommentStateFixture
    {
        SlashLineCommentStateFixture()
            : info("test.dot")
        {
        }
        
        FileInfo info;
        Token token;
        std::deque<TokenInfo> tokens;
        states::SlashLineCommentState state;
    };
    
    TEST_FIXTURE(SlashLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(SlashLineCommentStateFixture, verifyNewLineProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::SlashLineComment, state.consume('a', info, token, tokens));
        CHECK_EQUAL(TokenizerState::SlashLineComment, state.consume('b', info, token, tokens));
        CHECK_EQUAL(TokenizerState::SlashLineComment, state.consume('c', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Init, state.consume('\n', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(SlashLineCommentStateFixture, verifyLineEscapeMovesUsToMultiLineEscape)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::SlashLineComment, state.consume('a', info, token, tokens));
        CHECK_EQUAL(TokenizerState::SlashLineComment, state.consume('b', info, token, tokens));
        CHECK_EQUAL(TokenizerState::SlashLineComment, state.consume('c', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineEscape, state.consume('\\', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(0U, tokens.size());
        CHECK(info.empty()); // token not yet generated, empty
    }
}

