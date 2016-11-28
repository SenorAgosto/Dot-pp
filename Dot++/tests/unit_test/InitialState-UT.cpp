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
        InitStateFixture()
            : nextState(dot_pp::TokenizerState::Init)
            , info("test.dot")
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
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());
    }
    
    TEST_FIXTURE(InitStateFixture, verifyTabMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\t', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());
    }

    TEST_FIXTURE(InitStateFixture, verifyNewLineMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\n', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());
    }
    
    TEST_FIXTURE(InitStateFixture, verifyCarriageReturnMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\r', info, token, tokens));

        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());
    }
    
    TEST_FIXTURE(InitStateFixture, verifyQuoteMovesUsToStringLiteral)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('"', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());
    }
    
    TEST_FIXTURE(InitStateFixture, verifyHashMovesUsToHashLineComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('#', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());
    }
    
    TEST_FIXTURE(InitStateFixture, verifySlashMovesUsToSlashComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('/', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());
    }
    
    TEST_FIXTURE(InitStateFixture, verifyLeftBracketProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('[', info, token, tokens));

        REQUIRE CHECK_EQUAL(2U, tokens.size());
        CHECK_EQUAL("", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());
        
        CHECK_EQUAL("[", tokens[1].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::l_bracket, tokens[1].token().type());
    }

    TEST_FIXTURE(InitStateFixture, verifyRightBracketProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume(']', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(2U, tokens.size());
        CHECK_EQUAL("", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());
        
        CHECK_EQUAL("]", tokens[1].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::r_bracket, tokens[1].token().type());
    }

    TEST_FIXTURE(InitStateFixture, verifyEqualProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
            
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('=', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(2U, tokens.size());
        CHECK_EQUAL("", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].token().type());
        
        CHECK_EQUAL("=", tokens[1].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::equal, tokens[1].token().type());
    }

}

