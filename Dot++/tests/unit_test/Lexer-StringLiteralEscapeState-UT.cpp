#include "./platform/UnitTestSupport.hpp"

#include <Dot++/lexer/FileInfo.hpp>
#include <Dot++/lexer/states/StringLiteralEscapeState.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include <deque>

namespace {
    
    using namespace dot_pp::lexer;
    
    struct StringLiteralEscapeStateFixture
    {
        StringLiteralEscapeStateFixture()
            : info("test.dot")
        {
        }
        
        FileInfo info;
        Token token;
        std::deque<TokenInfo> tokens;
        states::StringLiteralEscapeState state;
    };
    
    TEST_FIXTURE(StringLiteralEscapeStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(StringLiteralEscapeStateFixture, verifyFunctionality)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::StringLiteral, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(TokenizerState::StringLiteral, state.consume('"', info, token, tokens));
        
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(" \"", token.to_string());
        CHECK(info.empty());    // token not yet generated, empty
    }
}

