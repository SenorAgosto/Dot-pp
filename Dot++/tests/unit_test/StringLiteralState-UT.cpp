#include "./platform/UnitTestSupport.hpp"

#include <Dot++/lexer/FileInfo.hpp>
#include <Dot++/lexer/states/StringLiteralState.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include <deque>

namespace {
    
    using namespace dot_pp::lexer;
    
    struct StringLiteralStateFixture
    {
        StringLiteralStateFixture()
            : info("test.dot")
        {
        }
        
        FileInfo info;
        Token token;
        std::deque<TokenInfo> tokens;
        states::StringLiteralState state;
    };
    
    TEST_FIXTURE(StringLiteralStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(StringLiteralStateFixture, verifyAppendingUntilWeEncounterEndQuote)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::StringLiteral, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(TokenizerState::StringLiteral, state.consume('a', info, token, tokens));
        CHECK_EQUAL(TokenizerState::StringLiteral, state.consume('/', info, token, tokens));
        CHECK_EQUAL(TokenizerState::StringLiteral, state.consume('#', info, token, tokens));
        CHECK_EQUAL(TokenizerState::StringLiteral, state.consume('[', info, token, tokens));
        CHECK_EQUAL(TokenizerState::StringLiteral, state.consume(']', info, token, tokens));
        CHECK_EQUAL(TokenizerState::StringLiteral, state.consume('=', info, token, tokens));
        CHECK_EQUAL(TokenizerState::StringLiteral, state.consume('\'', info, token, tokens));
        CHECK_EQUAL(TokenizerState::StringLiteral, state.consume('\n', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Init, state.consume('"', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL(" a/#[]=\'\n", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::string_literal, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(2U, tokens[0].fileInfo().end().line());     // the last input is \n, puts us on 2nd line 1st column
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(StringLiteralStateFixture, verifyBackslashMovesToEscapeState)
    {
        CHECK_EQUAL(TokenizerState::StringLiteralEscape, state.consume('\\', info, token, tokens));
    }
}

