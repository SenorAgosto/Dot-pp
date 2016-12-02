#include "./platform/UnitTestSupport.hpp"

#include <Dot++/lexer/FileInfo.hpp>
#include <Dot++/lexer/states/InitialState.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include <deque>

namespace {
    
    using namespace dot_pp::lexer;
    
    struct InitStateFixture
    {
        InitStateFixture(const std::string& t="")
            : nextState(TokenizerState::Init)
            , info("test.dot")
            , token(t, TokenType::comment)
        {
        }
        
        TokenizerState nextState;
        
        FileInfo info;
        Token token;
        
        std::deque<TokenInfo> tokens;
        states::InitialState state;
    };
    
    TEST_FIXTURE(InitStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(InitStateFixture, verifySpaceMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        
        CHECK_EQUAL(TokenizerState::Init, state.consume('t', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Init, state.consume('o', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Init, state.consume('k', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Init, state.consume('e', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Init, state.consume('n', info, token, tokens));
        CHECK_EQUAL(TokenizerState::Init, state.consume(' ', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("token", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(6U, tokens[0].fileInfo().end().column());
    }
    
    struct InitStateWithTokenFixture : public InitStateFixture
    {
        InitStateWithTokenFixture()
            : InitStateFixture("abc")
        {
        }
    };
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifyTabMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(TokenizerState::Init, state.consume('\t', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }

    TEST_FIXTURE(InitStateWithTokenFixture, verifyNewLineMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(TokenizerState::Init, state.consume('\n', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifyCarriageReturnMovesUsToInitAndProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(TokenizerState::Init, state.consume('\r', info, token, tokens));

        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifyQuoteMovesUsToStringLiteral)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(TokenizerState::StringLiteral, state.consume('"', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifyHashMovesUsToHashLineComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(TokenizerState::HashLineComment, state.consume('#', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifySlashMovesUsToSlashComment)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(TokenizerState::SlashLineComment, state.consume('/', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());
    }
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifyLeftBracketProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(TokenizerState::Init, state.consume('[', info, token, tokens));

        REQUIRE CHECK_EQUAL(2U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());


        CHECK_EQUAL("[", tokens[1].token().to_string());
        CHECK_EQUAL(TokenType::l_bracket, tokens[1].token().type());
        
        CHECK_EQUAL(1U, tokens[1].fileInfo().start().line());
        CHECK_EQUAL(4U, tokens[1].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[1].fileInfo().end().line());
        CHECK_EQUAL(5U, tokens[1].fileInfo().end().column());
    }

    TEST_FIXTURE(InitStateWithTokenFixture, verifyRightBracketProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(TokenizerState::Init, state.consume(']', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(2U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());

        CHECK_EQUAL("]", tokens[1].token().to_string());
        CHECK_EQUAL(TokenType::r_bracket, tokens[1].token().type());
        CHECK_EQUAL(1U, tokens[1].fileInfo().start().line());
        CHECK_EQUAL(4U, tokens[1].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[1].fileInfo().end().line());
        CHECK_EQUAL(5U, tokens[1].fileInfo().end().column());
    }

    TEST_FIXTURE(InitStateWithTokenFixture, verifyEqualProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
            
        CHECK_EQUAL(TokenizerState::Init, state.consume('=', info, token, tokens));
        
        REQUIRE CHECK_EQUAL(2U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());

        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());

        CHECK_EQUAL("=", tokens[1].token().to_string());
        CHECK_EQUAL(TokenType::equal, tokens[1].token().type());
        CHECK_EQUAL(1U, tokens[1].fileInfo().start().line());
        CHECK_EQUAL(4U, tokens[1].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[1].fileInfo().end().line());
        CHECK_EQUAL(5U, tokens[1].fileInfo().end().column());
    }
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifyLeftParenProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(TokenizerState::Init, state.consume('{', info, token, tokens));

        REQUIRE CHECK_EQUAL(2U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());


        CHECK_EQUAL("{", tokens[1].token().to_string());
        CHECK_EQUAL(TokenType::l_paren, tokens[1].token().type());
        
        CHECK_EQUAL(1U, tokens[1].fileInfo().start().line());
        CHECK_EQUAL(4U, tokens[1].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[1].fileInfo().end().line());
        CHECK_EQUAL(5U, tokens[1].fileInfo().end().column());
    }
    
    TEST_FIXTURE(InitStateWithTokenFixture, verifyRightParenProducesToken)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(TokenizerState::Init, state.consume('}', info, token, tokens));

        REQUIRE CHECK_EQUAL(2U, tokens.size());
        
        CHECK_EQUAL("abc", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[0].token().type());
        
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().line());
        CHECK_EQUAL(1U, tokens[0].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[0].fileInfo().end().line());
        CHECK_EQUAL(4U, tokens[0].fileInfo().end().column());


        CHECK_EQUAL("}", tokens[1].token().to_string());
        CHECK_EQUAL(TokenType::r_paren, tokens[1].token().type());
        
        CHECK_EQUAL(1U, tokens[1].fileInfo().start().line());
        CHECK_EQUAL(4U, tokens[1].fileInfo().start().column());
        CHECK_EQUAL(1U, tokens[1].fileInfo().end().line());
        CHECK_EQUAL(5U, tokens[1].fileInfo().end().column());
    }
    
}

