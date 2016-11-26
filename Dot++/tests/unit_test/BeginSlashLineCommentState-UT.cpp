#include "./platform/UnitTestSupport.hpp"

#include <Dot++/states/BeginSlashLineCommentState.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/Token.hpp>

#include <deque>

namespace {
    
    struct BeginSlashLineCommentStateFixture
    {
        BeginSlashLineCommentStateFixture()
            : token("abc", dot_pp::TokenType::string)
        {
        }
        
        dot_pp::Token token;
        std::deque<dot_pp::Token> tokens;
        dot_pp::states::BeginSlashLineCommentState state;
    };
    
    TEST_FIXTURE(BeginSlashLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(BeginSlashLineCommentStateFixture, verifySlashMovesUsToComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('/', token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("abc", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].type());
    }
    
    TEST_FIXTURE(BeginSlashLineCommentStateFixture, verifyStarMovesUsToMultiLineComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('*', token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("abc", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].type());
    }
    
    TEST_FIXTURE(BeginSlashLineCommentStateFixture, verifyEverythingElseMovesUsToInit)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('a', token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("abc", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].type());
    }
}

