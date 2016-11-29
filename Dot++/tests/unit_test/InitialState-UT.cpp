#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include <Dot++/states/InitialState.hpp>
#include <Dot++/Token.hpp>
#include <Dot++/TokenInfo.hpp>
#include <Dot++/TokenizerState.hpp>

#include <deque>

namespace {
    
    struct InitStateFixture
    {
        InitStateFixture(const std::string& t="")
            : nextState(dot_pp::TokenizerState::Init)
            , info("test.dot")
            , token(t, dot_pp::TokenType::comment)
        {
        }
        
        dot_pp::TokenizerState nextState;
        
        dot_pp::FileInfo info;
        dot_pp::Token token;
        
        std::deque<dot_pp::TokenInfo> tokens;
        dot_pp::states::InitialState state;
    };
    
    TEST_FIXTURE(InitStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(InitStateFixture, verifySpaceMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('t', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('o', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('k', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('e', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('n', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume(' ', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("token", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(6U, tokens[0].fileInfo().end().column());
    }
    
    struct InitStateWithTokenFixture : public InitStateFixture
    {
        InitStateWithTokenFixture()
            : InitStateFixture("abc")
        {
        }
    };
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifyTabMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\t', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }

    TEST_FIXTURE(InitStateWithTokenFixture, verifyNewLineMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\n', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifyCarriageReturnMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\r', info, token, tokens));

        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifyQuoteMovesUsToStringLiteral)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('"', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifyHashMovesUsToHashLineComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('#', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifySlashMovesUsToSlashComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('/', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifyLeftBracketProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('[', info, token, tokens));

        REQUIRE CHECK_EQUAL(2U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());


        CHECK_EQUAL("[", tokens[1].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::l_bracket, tokens[1].token().type());
        
        CHECK_EQUAL(1U, tokens[1].fileInfo().start().line());
        CHECK_EQUAL(4U, tokens[1].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[1].fileInfo().end().line());
        CHECK_EQUAL(5U, tokens[1].fileInfo().end().column());
    }

    TEST_FIXTURE(InitStateWithTokenFixture, verifyRightBracketProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume(']', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(2U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());

        CHECK_EQUAL("]", tokens[1].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::r_bracket, tokens[1].token().type());
        CHECK_EQUAL(1U, tokens[1].fileInfo().start().line());
        CHECK_EQUAL(4U, tokens[1].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[1].fileInfo().end().line());
        CHECK_EQUAL(5U, tokens[1].fileInfo().end().column());
    }

    TEST_FIXTURE(InitStateWithTokenFixture, verifyEqualProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
            
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('=', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(2U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());

        CHECK_EQUAL("=", tokens[1].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::equal, tokens[1].token().type());
        CHECK_EQUAL(1U, tokens[1].fileInfo().start().line());
        CHECK_EQUAL(4U, tokens[1].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[1].fileInfo().end().line());
        CHECK_EQUAL(5U, tokens[1].fileInfo().end().column());
    }
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifyLeftParenProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('{', info, token, tokens));

        REQUIRE CHECK_EQUAL(2U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());


        CHECK_EQUAL("{", tokens[1].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::l_paren, tokens[1].token().type());
        
        CHECK_EQUAL(1U, tokens[1].fileInfo().start().line());
        CHECK_EQUAL(4U, tokens[1].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[1].fileInfo().end().line());
        CHECK_EQUAL(5U, tokens[1].fileInfo().end().column());
    }
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifyRightParenProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('}', info, token, tokens));

        REQUIRE CHECK_EQUAL(2U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());


        CHECK_EQUAL("}", tokens[1].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::r_paren, tokens[1].token().type());
        
        CHECK_EQUAL(1U, tokens[1].fileInfo().start().line());
        CHECK_EQUAL(4U, tokens[1].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[1].fileInfo().end().line());
        CHECK_EQUAL(5U, tokens[1].fileInfo().end().column());
    }
    
}

