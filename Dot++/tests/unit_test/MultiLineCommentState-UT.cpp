#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include <Dot++/states/MultiLineCommentState.hpp>
#include <Dot++/Token.hpp>
#include <Dot++/TokenInfo.hpp>
#include <Dot++/TokenizerState.hpp>

#include <deque>

namespace {
    
    struct MultiLineCommentStateFixture
    {
        MultiLineCommentStateFixture()
            : info("test.dot")
        {
        }
        
        dot_pp::FileInfo info;
        dot_pp::Token token;
        std::deque<dot_pp::TokenInfo> tokens;
        dot_pp::states::MultiLineCommentState state;
    };
    
    TEST_FIXTURE(MultiLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(MultiLineCommentStateFixture, verifyFunctionality)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('a', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('/', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('#', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('[', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume(']', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('\\', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('=', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('\'', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('"', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::MultiLineComment, state.consume('\n', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::EndMultiLineComment, state.consume('*', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(" a/#[]\\=\'\"\n", token.to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, token.type());
    }
    
}

