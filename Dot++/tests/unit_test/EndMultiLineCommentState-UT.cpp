#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include <Dot++/states/EndMultiLineCommentState.hpp>
#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/TokenInfo.hpp>

#include <deque>

namespace {
    
    struct EndMultiLineCommentStateFixture
    {
        EndMultiLineCommentStateFixture()
            : info("test.dot")
        {
        }
        
        dot_pp::FileInfo info;
        dot_pp::Token token;
        std::deque<dot_pp::TokenInfo> tokens;
        dot_pp::states::EndMultiLineCommentState state;
    };
    
    TEST_FIXTURE(EndMultiLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(EndMultiLineCommentStateFixture, verifyFunctionality)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('a', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('#', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('[', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume(']', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('\\', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('=', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('\'', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('"', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('\n', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('/', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        CHECK_EQUAL(" a#[]\\=\'\"\n", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::multiline_comment, tokens[0].token().type());
    }
}

