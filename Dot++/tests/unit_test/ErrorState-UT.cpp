#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include <Dot++/states/ErrorState.hpp>
#include <Dot++/Token.hpp>
#include <Dot++/TokenInfo.hpp>
#include <Dot++/TokenizerState.hpp>

#include <deque>

namespace {
    
    struct ErrorStateFixture
    {
        ErrorStateFixture()
            : info("test.dot")
        {
        }
        
        dot_pp::FileInfo info;
        dot_pp::Token token;
        std::deque<dot_pp::TokenInfo> tokens;
        dot_pp::states::ErrorState state;
    };
    
    TEST_FIXTURE(ErrorStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(ErrorStateFixture, verifyWeAlwaysStayInErrorState)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('a', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('/', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('#', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('[', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume(']', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('\\', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('=', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('\'', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('"', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Error, state.consume('\n', info, token, tokens));
        
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(1U, info.start().line());
        CHECK_EQUAL(1U, info.start().column());
        CHECK_EQUAL(1U, info.end().line());
        CHECK_EQUAL(1U, info.end().column());
    }
}

