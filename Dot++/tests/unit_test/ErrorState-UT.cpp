#include "./platform/UnitTestSupport.hpp"

#include <Dot++/states/ErrorState.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/Token.hpp>

#include <deque>

namespace {
    
    struct ErrorStateFixture
    {
        dot_pp::Token token;
        std::deque<dot_pp::Token> tokens;
        dot_pp::ErrorState state;
    };
    
    TEST_FIXTURE(ErrorStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(ErrorStateFixture, verifyWeAlwaysStayInErrorState)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume(' ', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('a', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('/', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('#', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('[', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume(']', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('\\', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('=', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('\'', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('"', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('\n', token, tokens));
        
        CHECK_EQUAL(0U, tokens.size());
    }
}

