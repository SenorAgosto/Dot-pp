#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Exceptions.hpp>
#include <Dot++/NullConstructionPolicy.hpp>

#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/parser/states/ReadLeftBracketVertexAttributeState.hpp>

namespace {
    
    using namespace dot_pp::lexer;
    using namespace dot_pp::parser;
    
    struct InitialStateFixture
    {
        TokenStack attributes;
        TokenStack stack;
        
        dot_pp::NullConstructionPolicy constructor;
        states::ReadLeftBracketVertexAttributeState<dot_pp::NullConstructionPolicy> state;
    };
    
    TEST_FIXTURE(InitialStateFixture, verifyInstatiation)
    {
    }

    TEST_FIXTURE(InitialStateFixture, verifyTransitionsToReadVertexAttributeName)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("attribute1", TokenType::string), FileInfo("test.dot"));

        auto handle = tokens.cbegin();
        
        CHECK_EQUAL(ParserState::ReadVertexAttributeName, state.consume(handle++, stack, attributes, constructor));
        
        CHECK_EQUAL(1U, attributes.size());
        CHECK_EQUAL(0U, stack.size());
    }
    
    TEST_FIXTURE(InitialStateFixture, verifyTransitionsToGraphAttributeValue)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("]", TokenType::r_bracket), FileInfo("test.dot"));

        auto handle = tokens.cbegin();
        
        // we share this state with graph attributes
        CHECK_EQUAL(ParserState::ReadGraphAttributeValue, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(0U, stack.size());
    }
    
    TEST_FIXTURE(InitialStateFixture, verifyThrowsOnWrongTokenType)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("keyword", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("string_lit", TokenType::string_literal), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_paren", TokenType::l_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_paren", TokenType::r_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::directed_edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_bracket", TokenType::l_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("equal", TokenType::equal), FileInfo("test.dot"));
        tokens.emplace_back(Token("end_statement", TokenType::end_statement), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah blah", TokenType::comment), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah \n blah", TokenType::multiline_comment), FileInfo("test.dot"));
        
        for(auto handle = tokens.cbegin(), end = tokens.cend(); handle != end; ++handle)
        {
            CHECK_THROW(state.consume(handle, stack, attributes, constructor), dot_pp::SyntaxError);
        }
    }
}
