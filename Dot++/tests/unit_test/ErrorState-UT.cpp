#include "./platform/UnitTestSupport.hpp"

#include <Dot++/lexer/FileInfo.hpp>
#include <Dot++/lexer/states/ErrorState.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include <deque>

namespace {
    
    using namespace dot_pp::lexer;
    
    struct ErrorStateFixture
    {
        ErrorStateFixture()
            : info("test.dot")
        {
        }
        
        FileInfo info;
        Token token;
        std::deque<TokenInfo> tokens;
        states::ErrorState state;
    };
    
    TEST_FIXTURE(ErrorStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(ErrorStateFixture, verifyWeAlwaysStayInErrorState)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::Error, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Error, state.consume('a', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Error, state.consume('/', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Error, state.consume('#', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Error, state.consume('[', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Error, state.consume(']', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Error, state.consume('\\', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Error, state.consume('=', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Error, state.consume('\'', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Error, state.consume('"', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Error, state.consume('\n', info, token, tokens));
        
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(1U, info.start().line());
        CHECK_EQUAL(1U, info.start().column());
        CHECK_EQUAL(1U, info.end().line());
        CHECK_EQUAL(1U, info.end().column());
    }
}

