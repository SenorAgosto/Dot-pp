#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include <Dot++/states/HashLineCommentState.hpp>
#include <Dot++/Token.hpp>
#include <Dot++/TokenInfo.hpp>
#include <Dot++/TokenizerState.hpp>

#include <deque>

namespace {
    
    struct HashLineCommentStateFixture
    {
        HashLineCommentStateFixture()
            : info("test.dot")
        {
        }
        
        dot_pp::FileInfo info;
        dot_pp::Token token;
        std::deque<dot_pp::TokenInfo> tokens;
        dot_pp::states::HashLineCommentState state;
    };
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyWeAppendToTokenUntilNewLine)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('a', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('/', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('#', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('[', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(']', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('\\', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('=', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('\'', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('"', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\n', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL(" a/#[]\\=\'\"", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(11U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyTokenProduction)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('t', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('h', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('i', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('s', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('i', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('s', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('a', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('c', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('o', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('m', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('m', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('e', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('n', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('t', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\n', info, token, tokens));

        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL(" this is a comment", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(19U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyCarriageReturnIsIgnored)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('y', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('e', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('s', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::HashLineComment, state.consume('\r', info, token, tokens));
        CHECK_EQUAL(dot_pp::TokenizerState::Init, state.consume('\n', info, token, tokens));

        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("yes", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
}

