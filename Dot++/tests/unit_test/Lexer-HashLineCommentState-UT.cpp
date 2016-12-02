#include "./platform/UnitTestSupport.hpp"

#include <Dot++/lexer/FileInfo.hpp>
#include <Dot++/lexer/states/HashLineCommentState.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include <deque>

namespace {
    
    using namespace dot_pp::lexer;
    
    struct HashLineCommentStateFixture
    {
        HashLineCommentStateFixture()
            : info("test.dot")
        {
        }
        
        FileInfo info;
        Token token;
        std::deque<TokenInfo> tokens;
        states::HashLineCommentState state;
    };
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyWeAppendToTokenUntilNewLine)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('a', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('/', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('#', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('[', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume(']', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('\\', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('=', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('\'', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('"', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Init, state.consume('\n', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL(" a/#[]\\=\'\"", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(11U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyTokenProduction)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('t', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('h', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('i', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('s', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('i', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('s', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('a', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('c', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('o', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('m', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('m', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('e', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('n', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('t', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Init, state.consume('\n', info, token, tokens));

        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL(" this is a comment", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(19U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(HashLineCommentStateFixture, verifyCarriageReturnIsIgnored)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('y', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('e', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('s', info, token, tokens));
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('\r', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Init, state.consume('\n', info, token, tokens));

        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("yes", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
}

