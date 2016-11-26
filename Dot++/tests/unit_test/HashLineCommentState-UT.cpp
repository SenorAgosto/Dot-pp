#include "./platform/UnitTestSupport.hpp"

#include <Dot++/states/HashLineCommentState.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/Token.hpp>

#include <deque>

namespace {
    
    struct HashLineCommentStateFixture
    {
        dot_pp::Token token;
        std::deque<dot_pp::Token> tokens;
        dot_pp::states::HashLineCommentState state;
    };
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyWeAppendToTokenUntilNewLine)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('a', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('/', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('#', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('[', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(']', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('\\', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('=', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('\'', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('"', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\n', token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL(" a/#[]\\=\'\"", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, token.type());
    }
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyTokenProduction)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('t', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('h', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('i', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('s', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('i', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('s', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('a', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('c', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('o', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('m', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('m', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('e', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('n', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('t', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\n', token, tokens));

        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL(" this is a comment", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, token.type());
    }
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyCarriageReturnIsIgnored)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('y', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('e', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('s', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('\r', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\n', token, tokens));

        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL("yes", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, token.type());
    }
}

