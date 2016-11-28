#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include <Dot++/states/StringLiteralState.hpp>
#include <Dot++/Token.hpp>
#include <Dot++/TokenInfo.hpp>
#include <Dot++/TokenizerState.hpp>

#include <deque>

namespace {
    
    struct StringLiteralStateFixture
    {
        StringLiteralStateFixture()
            : info("test.dot")
        {
        }
        
        dot_pp::FileInfo info;
        dot_pp::Token token;
        std::deque<dot_pp::TokenInfo> tokens;
        dot_pp::states::StringLiteralState state;
    };
    
    TEST_FIXTURE(StringLiteralStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(StringLiteralStateFixture, verifyAppendingUntilWeEncounterEndQuote)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('a', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('/', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('#', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('[', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume(']', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('=', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('\'', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('\n', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('"', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL(" a/#[]=\'\n", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string_literal, tokens[0].token().type());
    }
    
    TEST_FIXTURE(StringLiteralStateFixture, verifyBackslashMovesToEscapeState)
    {
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteralEscape, state.consume('\\', info, token, tokens));
    }
}

