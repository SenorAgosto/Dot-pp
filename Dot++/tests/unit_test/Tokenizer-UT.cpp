#include "./platform/UnitTestSupport.hpp"

#include <Dot++/lexer/Tokenizer.hpp>
#include <deque>
#include <sstream>

namespace {
    
    using namespace dot_pp::lexer;
    
    struct TokenizerFixture
    {
        TokenizerFixture()
            : tokenizer("test.dot")
        {
        }
        
        Tokenizer tokenizer;
        std::deque<TokenInfo> tokens;
    };
    
    TEST_FIXTURE(TokenizerFixture, verifyInstantation)
    {
    }
    
    TEST_FIXTURE(TokenizerFixture, verifyTokenizationOfWhitespace)
    {
        std::stringstream ss;
        ss << "    \t \n\r\t   \t";
        
        for(const auto c : ss.str())
        {
            tokenizer.consume(c, tokens);
        }
        
        REQUIRE CHECK_EQUAL(0U, tokens.size());
    }
    
    TEST_FIXTURE(TokenizerFixture, verifyTokenizeGraph)
    {
        std::stringstream ss;
        ss  << "digraph test {" "\n"
            << "\t" "a -> b;" "\n"
            << "\t" "a -> c;" "\n"
            << "}\n";
        
        for(const auto c : ss.str())
        {
            tokenizer.consume(c, tokens);
        }
        
        REQUIRE CHECK_EQUAL(12U, tokens.size());
        
        CHECK_EQUAL("digraph", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::keyword, tokens[0].token().type());
        
        CHECK_EQUAL("test", tokens[1].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[1].token().type());
        
        CHECK_EQUAL("{", tokens[2].token().to_string());
        CHECK_EQUAL(TokenType::l_paren, tokens[2].token().type());
        
        CHECK_EQUAL("a", tokens[3].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[3].token().type());
        
        CHECK_EQUAL("->", tokens[4].token().to_string());
        CHECK_EQUAL(TokenType::directed_edge, tokens[4].token().type());

        CHECK_EQUAL("b", tokens[5].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[5].token().type());
        
        CHECK_EQUAL(";", tokens[6].token().to_string());
        CHECK_EQUAL(TokenType::end_statement, tokens[6].token().type());
        
        CHECK_EQUAL("a", tokens[7].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[7].token().type());
        
        CHECK_EQUAL("->", tokens[8].token().to_string());
        CHECK_EQUAL(TokenType::directed_edge, tokens[8].token().type());

        CHECK_EQUAL("c", tokens[9].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[9].token().type());

        CHECK_EQUAL(";", tokens[10].token().to_string());
        CHECK_EQUAL(TokenType::end_statement, tokens[10].token().type());

        CHECK_EQUAL("}", tokens[11].token().to_string());
        CHECK_EQUAL(TokenType::r_paren, tokens[11].token().type());
    }

    TEST_FIXTURE(TokenizerFixture, verifyTokenizeGraphWithComments)
    {
        std::stringstream ss;
        ss  << "digraph test {" "\n"
            << "// comment one" "\n"
            << "\t" "a -> b;" "\n"
            << "# comment two" "\n"
            << "\t" "a -> c;" "\n"
            << "// comment three" "\\\n"
            << " continued \n"
            << "   /* comment four \n"
            << "      continued \n"
            << "      continued */" "\n"
            << "}\n";
        
        for(const auto c : ss.str())
        {
            tokenizer.consume(c, tokens);
        }
        
        REQUIRE CHECK_EQUAL(16U, tokens.size());
        
        CHECK_EQUAL("digraph", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::keyword, tokens[0].token().type());
        
        CHECK_EQUAL("test", tokens[1].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[1].token().type());
        
        CHECK_EQUAL("{", tokens[2].token().to_string());
        CHECK_EQUAL(TokenType::l_paren, tokens[2].token().type());

        CHECK_EQUAL(" comment one", tokens[3].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[3].token().type());
        
        CHECK_EQUAL("a", tokens[4].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[4].token().type());
        
        CHECK_EQUAL("->", tokens[5].token().to_string());
        CHECK_EQUAL(TokenType::directed_edge, tokens[5].token().type());

        CHECK_EQUAL("b", tokens[6].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[6].token().type());
        
        CHECK_EQUAL(";", tokens[7].token().to_string());
        CHECK_EQUAL(TokenType::end_statement, tokens[7].token().type());
        
        CHECK_EQUAL(" comment two", tokens[8].token().to_string());
        CHECK_EQUAL(TokenType::comment, tokens[8].token().type());
        
        CHECK_EQUAL("a", tokens[9].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[9].token().type());
        
        CHECK_EQUAL("->", tokens[10].token().to_string());
        CHECK_EQUAL(TokenType::directed_edge, tokens[10].token().type());

        CHECK_EQUAL("c", tokens[11].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[11].token().type());

        CHECK_EQUAL(";", tokens[12].token().to_string());
        CHECK_EQUAL(TokenType::end_statement, tokens[12].token().type());

        CHECK_EQUAL(" comment three\n continued ", tokens[13].token().to_string());
        CHECK_EQUAL(TokenType::multiline_comment, tokens[13].token().type());

        CHECK_EQUAL(" comment four \n      continued \n      continued ", tokens[14].token().to_string());
        CHECK_EQUAL(TokenType::multiline_comment, tokens[14].token().type());

        CHECK_EQUAL("}", tokens[15].token().to_string());
        CHECK_EQUAL(TokenType::r_paren, tokens[15].token().type());
    }

    TEST_FIXTURE(TokenizerFixture, verifyTokenizeGraphWithGraphAttributes)
    {
        std::stringstream ss;
        ss  << "digraph test {" "\n"
        
            << "\t" "size=\"1,1\";" "\n"
        
            << "\t" "a -> b;" "\n"
            << "\t" "a -> c;" "\n"
            << "}\n";
        
        for(const auto c : ss.str())
        {
            tokenizer.consume(c, tokens);
        }
        
        REQUIRE CHECK_EQUAL(16U, tokens.size());
        
        CHECK_EQUAL("digraph", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::keyword, tokens[0].token().type());
        
        CHECK_EQUAL("test", tokens[1].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[1].token().type());
        
        CHECK_EQUAL("{", tokens[2].token().to_string());
        CHECK_EQUAL(TokenType::l_paren, tokens[2].token().type());
        
        CHECK_EQUAL("size", tokens[3].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[3].token().type());

        CHECK_EQUAL("=", tokens[4].token().to_string());
        CHECK_EQUAL(TokenType::equal, tokens[4].token().type());
        
        CHECK_EQUAL("1,1", tokens[5].token().to_string());
        CHECK_EQUAL(TokenType::string_literal, tokens[5].token().type());
        
        CHECK_EQUAL(";", tokens[6].token().to_string());
        CHECK_EQUAL(TokenType::end_statement, tokens[6].token().type());
        
        CHECK_EQUAL("a", tokens[7].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[7].token().type());
        
        CHECK_EQUAL("->", tokens[8].token().to_string());
        CHECK_EQUAL(TokenType::directed_edge, tokens[8].token().type());

        CHECK_EQUAL("b", tokens[9].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[9].token().type());
        
        CHECK_EQUAL(";", tokens[10].token().to_string());
        CHECK_EQUAL(TokenType::end_statement, tokens[10].token().type());
        
        CHECK_EQUAL("a", tokens[11].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[11].token().type());
        
        CHECK_EQUAL("->", tokens[12].token().to_string());
        CHECK_EQUAL(TokenType::directed_edge, tokens[12].token().type());

        CHECK_EQUAL("c", tokens[13].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[13].token().type());

        CHECK_EQUAL(";", tokens[14].token().to_string());
        CHECK_EQUAL(TokenType::end_statement, tokens[14].token().type());

        CHECK_EQUAL("}", tokens[15].token().to_string());
        CHECK_EQUAL(TokenType::r_paren, tokens[15].token().type());
    }

    TEST_FIXTURE(TokenizerFixture, verifyTokenizeGraphWithEdgeAttributes)
    {
        std::stringstream ss;
        ss  << "digraph test {" "\n"
            << "\t" "a -> b -> c -> d;" "\n"
            << "\t" "a -> c [label=arc attr=\"g'\"];" "\n"
            << "}\n";
        
        for(const auto c : ss.str())
        {
            tokenizer.consume(c, tokens);
        }
        
        REQUIRE CHECK_EQUAL(24U, tokens.size());
        
        CHECK_EQUAL("digraph", tokens[0].token().to_string());
        CHECK_EQUAL(TokenType::keyword, tokens[0].token().type());
        
        CHECK_EQUAL("test", tokens[1].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[1].token().type());
        
        CHECK_EQUAL("{", tokens[2].token().to_string());
        CHECK_EQUAL(TokenType::l_paren, tokens[2].token().type());
        
        CHECK_EQUAL("a", tokens[3].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[3].token().type());
        
        CHECK_EQUAL("->", tokens[4].token().to_string());
        CHECK_EQUAL(TokenType::directed_edge, tokens[4].token().type());

        CHECK_EQUAL("b", tokens[5].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[5].token().type());

        CHECK_EQUAL("->", tokens[6].token().to_string());
        CHECK_EQUAL(TokenType::directed_edge, tokens[6].token().type());

        CHECK_EQUAL("c", tokens[7].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[7].token().type());

        CHECK_EQUAL("->", tokens[8].token().to_string());
        CHECK_EQUAL(TokenType::directed_edge, tokens[8].token().type());
        
        CHECK_EQUAL("d", tokens[9].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[9].token().type());

        CHECK_EQUAL(";", tokens[10].token().to_string());
        CHECK_EQUAL(TokenType::end_statement, tokens[10].token().type());
        
        CHECK_EQUAL("a", tokens[11].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[11].token().type());
        
        CHECK_EQUAL("->", tokens[12].token().to_string());
        CHECK_EQUAL(TokenType::directed_edge, tokens[12].token().type());

        CHECK_EQUAL("c", tokens[13].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[13].token().type());

        CHECK_EQUAL("[", tokens[14].token().to_string());
        CHECK_EQUAL(TokenType::l_bracket, tokens[14].token().type());

        CHECK_EQUAL("label", tokens[15].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[15].token().type());

        CHECK_EQUAL("=", tokens[16].token().to_string());
        CHECK_EQUAL(TokenType::equal, tokens[16].token().type());

        CHECK_EQUAL("arc", tokens[17].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[17].token().type());

        CHECK_EQUAL("attr", tokens[18].token().to_string());
        CHECK_EQUAL(TokenType::string, tokens[18].token().type());

        CHECK_EQUAL("=", tokens[19].token().to_string());
        CHECK_EQUAL(TokenType::equal, tokens[19].token().type());

        CHECK_EQUAL("g'", tokens[20].token().to_string());
        CHECK_EQUAL(TokenType::string_literal, tokens[20].token().type());

        CHECK_EQUAL("]", tokens[21].token().to_string());
        CHECK_EQUAL(TokenType::r_bracket, tokens[21].token().type());

        CHECK_EQUAL(";", tokens[22].token().to_string());
        CHECK_EQUAL(TokenType::end_statement, tokens[22].token().type());

        CHECK_EQUAL("}", tokens[23].token().to_string());
        CHECK_EQUAL(TokenType::r_paren, tokens[23].token().type());
    }
}
