#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include <Dot++/states/StringLiteralEscapeState.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/Token.hpp>

#include <deque>

namespace {
    
    struct StringLiteralEscapeStateFixture
    {
        StringLiteralEscapeStateFixture()
            : info("test.dot")
            , token(info)
        {
        }
        
        dot_pp::FileInfo info;
        dot_pp::Token token;
        std::deque<dot_pp::Token> tokens;
        dot_pp::states::StringLiteralEscapeState state;
    };
    
    TEST_FIXTURE(StringLiteralEscapeStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(StringLiteralEscapeStateFixture, verifyFunctionality)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume(' ', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::StringLiteral, state.consume('"', token, tokens));
        
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(" \"", token.to_string());
    }
}

