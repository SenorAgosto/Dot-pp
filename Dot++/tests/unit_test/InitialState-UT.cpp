#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include <Dot++/states/InitialState.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/Token.hpp>

#include <deque>

namespace {
    
    struct InitStateFixture
    {
        InitStateFixture()
            : nextState(dot_pp::TokenizerState::Init)
            , info("test.dot")
            , token(info)
        {
        }
        
        dot_pp::TokenizerState nextState;
        
        dot_pp::FileInfo info;
        dot_pp::Token token;
        
        std::deque<dot_pp::Token> tokens;
        dot_pp::states::InitialState state;
    };
    
    TEST_FIXTURE(InitStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(InitStateFixture, verifySpaceMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('t', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('o', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('k', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('e', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('n', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume(' ', token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("token", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].type());
    }
    
    TEST_FIXTURE(InitStateFixture, verifyTabMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\t', token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].type());
    }

    TEST_FIXTURE(InitStateFixture, verifyNewLineMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\n', token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].type());
    }
    
    TEST_FIXTURE(InitStateFixture, verifyCarriageReturnMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\r', token, tokens));

        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].type());
    }
    
    TEST_FIXTURE(InitStateFixture, verifyQuoteMovesUsToStringLiteral)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('"', token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].type());
    }
    
    TEST_FIXTURE(InitStateFixture, verifyHashMovesUsToHashLineComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('#', token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].type());
    }
    
    TEST_FIXTURE(InitStateFixture, verifySlashMovesUsToSlashComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::SlashLineComment, state.consume('/', token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].type());
    }
    
    TEST_FIXTURE(InitStateFixture, verifyLeftBracketProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('[', token, tokens));

        REQUIRE CHECK_EQUAL(2U, tokens.size());
        CHECK_EQUAL("", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].type());
        
        CHECK_EQUAL("[", tokens[1].to_string());
        CHECK_EQUAL(dot_pp::TokenType::l_bracket, tokens[1].type());
    }

    TEST_FIXTURE(InitStateFixture, verifyRightBracketProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume(']', token, tokens));
        
        REQUIRE CHECK_EQUAL(2U, tokens.size());
        CHECK_EQUAL("", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].type());
        
        CHECK_EQUAL("]", tokens[1].to_string());
        CHECK_EQUAL(dot_pp::TokenType::r_bracket, tokens[1].type());
    }

    TEST_FIXTURE(InitStateFixture, verifyEqualProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
            
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('=', token, tokens));
        
        REQUIRE CHECK_EQUAL(2U, tokens.size());
        CHECK_EQUAL("", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[0].type());
        
        CHECK_EQUAL("=", tokens[1].to_string());
        CHECK_EQUAL(dot_pp::TokenType::equal, tokens[1].type());
    }

}

