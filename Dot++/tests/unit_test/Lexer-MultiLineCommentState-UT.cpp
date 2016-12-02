#include "./platform/UnitTestSupport.hpp"

#include <Dot++/lexer/FileInfo.hpp>
#include <Dot++/lexer/states/MultiLineCommentState.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include <deque>

namespace {
    
    using namespace dot_pp::lexer;
    
    struct MultiLineCommentStateFixture
    {
        MultiLineCommentStateFixture()
            : info("test.dot")
        {
        }
        
        FileInfo info;
        Token token;
        std::deque<TokenInfo> tokens;
        states::MultiLineCommentState state;
    };
    
    TEST_FIXTURE(MultiLineCommentStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(MultiLineCommentStateFixture, verifyFunctionality)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume(' ', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('a', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('/', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('#', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('[', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume(']', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('\\', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('=', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('\'', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('"', info, token, tokens));
        CHECK_EQUAL(TokenizerState::MultiLineComment, state.consume('\n', info, token, tokens));
        CHECK_EQUAL(TokenizerState::EndMultiLineComment, state.consume('*', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(" a/#[]\\=\'\"\n", token.to_string());
        CHECK_EQUAL(TokenType::string, token.type());
    }
    
}

