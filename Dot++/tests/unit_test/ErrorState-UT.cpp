#include "./platform/UnitTestSupport.hpp"

#include <Dot++/states/ErrorState.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/Token.hpp>

namespace {
    
    struct ErrorStateFixture
    {
        dot_pp::Token token;
        dot_pp::ErrorState state;
    };
    
    TEST_FIXTURE(ErrorStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(ErrorStateFixture, verifyWeAlwaysStayInErrorState)
    {
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume(' ', token));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('a', token));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('/', token));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('#', token));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('[', token));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume(']', token));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('\\', token));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('=', token));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('\'', token));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('"', token));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('\n', token));
        
        CHECK(!token.ready());
    }
}

