#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Exceptions.hpp>
#include <Dot++/NullConstructionPolicy.hpp>

#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/parser/states/ReadVertexAttributeEqualState.hpp>

namespace {
    
    using namespace dot_pp::lexer;
    using namespace dot_pp::parser;
    
    struct InitialStateFixture
    {
        TokenStack attributes;
        TokenStack stack;
        
        dot_pp::NullConstructionPolicy constructor;
        states::ReadVertexAttributeEqualState<dot_pp::NullConstructionPolicy> state;
    };
    
    TEST_FIXTURE(InitialStateFixture, verifyInstatiation)
    {
    }

    TEST_FIXTURE(InitialStateFixture, verifyTransitionsToReadLeftBracketVertexAttributeOnString)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("a", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("attribute", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("value", TokenType::string), FileInfo("test.dot"));

        auto handle = tokens.cbegin();
        stack.push(handle++);
        attributes.push(handle++);
        
        CHECK_EQUAL(1U, attributes.size());
        CHECK_EQUAL(1U, stack.size());
        
        CHECK_EQUAL(ParserState::ReadLeftBracketVertexAttribute, state.consume(handle++, stack, attributes, constructor));
        
        CHECK_EQUAL(0U, attributes.size());
        CHECK_EQUAL(1U, stack.size());
    }

    TEST_FIXTURE(InitialStateFixture, verifyTransitionsToReadLeftBracketVertexAttributeOnStringLiteral)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("a", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("attribute", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("g'", TokenType::string_literal), FileInfo("test.dot"));

        auto handle = tokens.cbegin();
        stack.push(handle++);
        attributes.push(handle++);
        
        CHECK_EQUAL(1U, attributes.size());
        CHECK_EQUAL(1U, stack.size());
        
        CHECK_EQUAL(ParserState::ReadLeftBracketVertexAttribute, state.consume(handle++, stack, attributes, constructor));
        
        CHECK_EQUAL(0U, attributes.size());
        CHECK_EQUAL(1U, stack.size());
    }
    
    TEST_FIXTURE(InitialStateFixture, verifyThrowsOnWrongTokenType)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("keyword", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_paren", TokenType::l_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_paren", TokenType::r_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::directed_edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_bracket", TokenType::l_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_bracket", TokenType::r_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("end_statement", TokenType::end_statement), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah blah", TokenType::comment), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah \n blah", TokenType::multiline_comment), FileInfo("test.dot"));
        
        for(auto handle = tokens.cbegin(), end = tokens.cend(); handle != end; ++handle)
        {
            CHECK_THROW(state.consume(handle, stack, attributes, constructor), dot_pp::SyntaxError);
        }
    }
}
