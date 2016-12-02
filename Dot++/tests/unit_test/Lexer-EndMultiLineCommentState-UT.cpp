#include "./platform/UnitTestSupport.hpp"

#include <Dot++/lexer/FileInfo.hpp>
#include <Dot++/lexer/states/EndMultiLineCommentState.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenizerState.hpp>
#include <Dot++/lexer/TokenInfo.hpp>

#include <deque>

namespace {
    
    using namespace dot_pp::lexer;
    
    struct EndMultiLineCommentStateFixture
    {
        EndMultiLineCommentStateFixture()
            : info("test.dot")
        {
        }
        
        FileInfo info;
        Token token;
        std::deque<TokenInfo> tokens;
        states::EndMultiLineCommentState state;
    };
    
    TEST_FIXTURE(EndMultiLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(EndMultiLineCommentStateFixture, verifyFunctionality)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('a', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('#', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('[', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume(']', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('\\', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('=', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('\'', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('"', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('\n', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Init, state.consume('/', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL(" a#[]\\=\'\"\n", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::multiline_comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(2U, tokens[0].fileInfo().end().line());     // last char is return, increment line
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().column());   // nothing after \n
    }
}

