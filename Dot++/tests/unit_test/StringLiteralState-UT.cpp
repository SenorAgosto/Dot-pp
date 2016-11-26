#include "./platform/UnitTestSupport.hpp"

#include <Dot++/states/StringLiteralState.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/Token.hpp>

#include <deque>

namespace {
    
    struct StringLiteralStateFixture
    {
        dot_pp::Token token;
        std::deque<dot_pp::Token> tokens;
        dot_pp::StringLiteralState state;
    };
    
    TEST_FIXTURE(StringLiteralStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(StringLiteralStateFixture, verifyAppendingUntilWeEncounterEndQuote)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume(' ', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('a', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('/', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('#', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('[', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume(']', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('=', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('\'', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('\n', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('"', token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL(" a/#[]=\'\n", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::string_literal, tokens[0].type());
    }
    
    TEST_FIXTURE(StringLiteralStateFixture, verifyBackslashMovesToEscapeState)
    {
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteralEscape, state.consume('\\', token, tokens));
    }
}

