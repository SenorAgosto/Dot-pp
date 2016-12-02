#include "./platform/UnitTestSupport.hpp"
#include "Dot++/src/lexer/states/ProduceToken.hpp"

#include <Dot++/lexer/FileInfo.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenizerState.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/lexer/TokenType.hpp>

#include <deque> 

namespace {
    
    using namespace dot_pp::lexer;
    
    struct ProduceTokenFixture
    {
        ProduceTokenFixture()
            : info("test.dot")
            , token("abcdefg", TokenType::string)
            , token2("abc\nabc", TokenType::multiline_comment)
        {
        }
        
        FileInfo info;
        Token token;
        Token token2;
        std::deque<TokenInfo> tokens;
    };
    
    TEST_FIXTURE(ProduceTokenFixture, verifyProduceTokenWithOneArgument)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(TokenizerState::Init, states::produceToken(TokenizerState::Init, tokens, token, info));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abcdefg", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[0].token().type());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(8U, tokens[0].fileInfo().end().column());
        
        
        CHECK_EQUAL(TokenizerState::Init, states::produceToken(TokenizerState::Init, tokens, token2, info, Token()));

        REQUIRE CHECK_EQUAL(2U, tokens.size());
        
        CHECK_EQUAL("abc\nabc", tokens[1].token().to_string());
        CHECK_EQUAL(TokenType::multiline_comment, tokens[1].token().type());
        CHECK_EQUAL(1U, tokens[1].fileInfo().start().line());
        CHECK_EQUAL(8U, tokens[1].fileInfo().start().column());
        CHECK_EQUAL(2U, tokens[1].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[1].fileInfo().end().column());
    }
}
