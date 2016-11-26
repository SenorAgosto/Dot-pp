#include "./platform/UnitTestSupport.hpp"

#include <Dot++/states/ErrorState.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/Token.hpp>
#include <Dot++/TokenInfo.hpp>

#include <deque>

namespace {
    
    struct ErrorStateFixture
    {
        ErrorStateFixture()
            : info("test.dot")
            , token(info)
        {
        }
        
        dot_pp::TokenInfo info;
        dot_pp::Token token;
        std::deque<dot_pp::Token> tokens;
        dot_pp::states::ErrorState state;
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

