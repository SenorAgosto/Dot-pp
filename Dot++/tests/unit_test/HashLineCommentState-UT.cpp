#include "./platform/UnitTestSupport.hpp"

#include <Dot++/states/HashLineCommentState.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/Token.hpp>

namespace {
    
    struct HashLineCommentStateFixture
    {
        dot_pp::Token token;
        dot_pp::HashLineCommentState state;
    };
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyWeAlwaysStayInErrorState)
    {
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('a', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('/', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('#', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('[', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(']', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('\\', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('=', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('\'', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('"', token));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\n', token));
    }
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyTokenProduction)
    {
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('t', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('h', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('i', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('s', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('i', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('s', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('a', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('c', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('o', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('m', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('m', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('e', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('n', token));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('t', token));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\n', token));
        
        CHECK_EQUAL(" this is a comment", token.to_string());
    }
}

