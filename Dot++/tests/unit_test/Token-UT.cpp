#include "./platform/UnitTestSupport.hpp"
#include <Dot++/Token.hpp>

namespace {

    TEST(verifyInstantation)
    {
        dot_pp::Token token;

        CHECK_EQUAL("", token.to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, token.type());
    }
    
    TEST(verifyInstantationWithValueAndType)
    {
        dot_pp::Token token("value", dot_pp::TokenType::comment);
        
        CHECK_EQUAL("value", token.to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, token.type());
    }
    
    TEST(verifySettingType)
    {
        dot_pp::Token token("value", dot_pp::TokenType::comment);
        
        CHECK_EQUAL("value", token.to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, token.type());

        token.type(dot_pp::TokenType::multiline_comment);
        CHECK_EQUAL(dot_pp::TokenType::multiline_comment, token.type());
    }
    
    TEST(verifyAppend)
    {
        dot_pp::Token token;
        CHECK_EQUAL("", token.to_string());
        
        token.append('a');
        CHECK_EQUAL("a", token.to_string());
    }
    
    TEST(verifyEmpty)
    {
        dot_pp::Token token;
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
        dot_pp::Token token("value", dot_pp::TokenType::comment);

        CHECK_EQUAL("value", token.to_string());
        CHECK_EQUAL(dot_pp::TokenType::comment, token.type());

        token.clear();
        
        CHECK_EQUAL("", token.to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, token.type());
        CHECK(token.empty());
    }
}
