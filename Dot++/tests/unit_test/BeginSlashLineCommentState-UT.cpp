#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include <Dot++/states/BeginSlashLineCommentState.hpp>
#include <Dot++/Token.hpp>
#include <Dot++/TokenInfo.hpp>
#include <Dot++/TokenizerState.hpp>

#include <deque>

namespace {
    
    struct BeginSlashLineCommentStateFixture
    {
        BeginSlashLineCommentStateFixture()
            : info("test.dot")
            , token("abc", dot_pp::TokenType::string)
        {
        }
        
        dot_pp::FileInfo info;
        dot_pp::Token token;
        std::deque<dot_pp::TokenInfo> tokens;
        dot_pp::states::BeginSlashLineCommentState state;
    };
    
    TEST_FIXTURE(BeginSlashLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(BeginSlashLineCommentStateFixture, verifySlashMovesUsToComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('/', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(BeginSlashLineCommentStateFixture, verifyStarMovesUsToMultiLineComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('*', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(BeginSlashLineCommentStateFixture, verifyEverythingElseMovesUsToInit)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('a', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
}

