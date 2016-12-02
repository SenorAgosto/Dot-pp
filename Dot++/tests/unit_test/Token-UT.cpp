#include "./platform/UnitTestSupport.hpp"
#include <Dot++/lexer/Token.hpp>

namespace {

    using namespace dot_pp::lexer;
    
    TEST(verifyInstantation)
    {
        Token token;

        CHECK_EQUAL("", token.to_string());
        CHECK_EQUAL(TokenType::string, token.type());
    }
    
    TEST(verifyInstantationWithValueAndType)
    {
        Token token("value", TokenType::comment);
        
        CHECK_EQUAL("value", token.to_string());
        CHECK_EQUAL(TokenType::comment, token.type());
    }
    
    TEST(verifySettingType)
    {
        Token token("value", TokenType::comment);
        
        CHECK_EQUAL("value", token.to_string());
        CHECK_EQUAL(TokenType::comment, token.type());

        token.type(TokenType::multiline_comment);
        CHECK_EQUAL(TokenType::multiline_comment, token.type());
    }
    
    TEST(verifyAppend)
    {
        Token token;
        CHECK_EQUAL("", token.to_string());
        
        token.append('a');
        CHECK_EQUAL("a", token.to_string());
    }
    
    TEST(verifyEmpty)
    {
        Token token;
        CHECK(token.empty());
        
        token.append('\t');
        CHECK(token.empty());
        
        token.append(' ');
        CHECK(token.empty());
        
        token.append('\n');
        CHECK(token.empty());
        
        token.append('\r');
        CHECK(token.empty());
        
        token.append('a');
        CHECK(!token.empty());
    }
    
    TEST(verifyClear)
    {
        Token token("value", TokenType::comment);

        CHECK_EQUAL("value", token.to_string());
        CHECK_EQUAL(TokenType::comment, token.type());

        token.clear();
        
        CHECK_EQUAL("", token.to_string());
        CHECK_EQUAL(TokenType::string, token.type());
        CHECK(token.empty());
    }
}
