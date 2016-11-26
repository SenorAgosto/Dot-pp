#include "./platform/UnitTestSupport.hpp"

#include <Dot++/states/EndMultiLineCommentState.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/Token.hpp>

#include <deque>

namespace {
    
    struct EndMultiLineCommentStateFixture
    {
        dot_pp::Token token;
        std::deque<dot_pp::Token> tokens;
        dot_pp::states::EndMultiLineCommentState state;
    };
    
    TEST_FIXTURE(EndMultiLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(EndMultiLineCommentStateFixture, verifyFunctionality)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume(' ', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('a', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('#', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('[', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume(']', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('\\', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('=', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('\'', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('"', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('\n', token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('/', token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL(" a#[]\\=\'\"\n", tokens[0].to_string());
        CHECK_EQUAL(dot_pp::TokenType::multiline_comment, tokens[0].type());
    }
}

