#include "./platform/UnitTestSupport.hpp"

#include <Dot++/lexer/FileInfo.hpp>
#include <Dot++/lexer/states/BeginSlashLineCommentState.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include <deque>

namespace {
    
    using namespace dot_pp::lexer;
    
    struct BeginSlashLineCommentStateFixture
    {
        BeginSlashLineCommentStateFixture()
            : info("test.dot")
            , token("abc", TokenType::string)
        {
        }
        
        FileInfo info;
        Token token;
        std::deque<TokenInfo> tokens;
        states::BeginSlashLineCommentState state;
    };
    
    TEST_FIXTURE(BeginSlashLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(BeginSlashLineCommentStateFixture, verifySlashMovesUsToComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::SlashLineComment, state.consume('/', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(BeginSlashLineCommentStateFixture, verifyStarMovesUsToMultiLineComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('*', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(BeginSlashLineCommentStateFixture, verifyEverythingElseMovesUsToInit)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::Init, state.consume('a', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
}

