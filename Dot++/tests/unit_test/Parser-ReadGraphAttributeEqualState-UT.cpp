#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/parser/states/ReadGraphAttributeEqualState.hpp>

#include <string>
#include <utility>

namespace {
    
    using namespace dot_pp::lexer;
    using namespace dot_pp::parser;

    struct NullConstructionPolicy
    {
        NullConstructionPolicy()
        {
        }
        
        void createGraph(const std::string&) {}
        void createDigraph(const std::string&) {}
        
        void createVertex(const std::string&) {}
        void createEdge(const std::string&, const std::string&){}
        
        void applyGraphAttribute(const std::string& attr, const std::string& value) { attribute = std::make_pair(attr, value); }
        void applyVertexAttribute(const std::string&, const std::string&, const std::string&) {}
        
        void applyEdgeAttribute(const std::string&, const std::string&, const std::string&, const std::string&) {}
        void finalize() {}
        
        std::pair<std::string, std::string> attribute;
    };
    
    struct ReadGraphAttributeEqualStateFixture
    {
        TokenStack attributes;
        TokenStack stack;
        
        NullConstructionPolicy constructor;
        states::ReadGraphAttributeEqualState<NullConstructionPolicy> state;
    };
    
    TEST_FIXTURE(ReadGraphAttributeEqualStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(ReadGraphAttributeEqualStateFixture, verifyTransitionsToGraphAttributeValueOnString)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("attributeName", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("attributeValue", TokenType::string), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        attributes.push(handle++);
        
        CHECK_EQUAL(1U, attributes.size());
        CHECK_EQUAL(0U, stack.size());
        
        CHECK_EQUAL(ParserState::ReadGraphAttributeValue, state.consume(handle++, stack, attributes, constructor));
        
        CHECK_EQUAL(0U, attributes.size());
        CHECK_EQUAL(0U, stack.size());
        
        CHECK_EQUAL("attributeName", constructor.attribute.first);
        CHECK_EQUAL("attributeValue", constructor.attribute.second);
    }

    TEST_FIXTURE(ReadGraphAttributeEqualStateFixture, verifyTransitionsToGraphAttributeValueOnStringLiteral)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("attributeName", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("attributeValue", TokenType::string_literal), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        attributes.push(handle++);
        
        CHECK_EQUAL(1U, attributes.size());
        CHECK_EQUAL(0U, stack.size());
        
        CHECK_EQUAL(ParserState::ReadGraphAttributeValue, state.consume(handle++, stack, attributes, constructor));

        CHECK_EQUAL(0U, attributes.size());
        CHECK_EQUAL(0U, stack.size());
        
        CHECK_EQUAL("attributeName", constructor.attribute.first);
        CHECK_EQUAL("attributeValue", constructor.attribute.second);
    }
    
    TEST_FIXTURE(ReadGraphAttributeEqualStateFixture, verifyThrowsOnInvalidTokens)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("keyword", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("directed_edge", TokenType::directed_edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_paren", TokenType::l_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_paren", TokenType::r_paren), FileInfo("test.dot"));
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
