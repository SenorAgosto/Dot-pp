#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Exceptions.hpp>
#include <Dot++/NullConstructionPolicy.hpp>

#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/parser/states/ReadAttributeEqualState.hpp>

#include <map>
#include <string>
#include <utility>

namespace {
    
    using namespace dot_pp::lexer;
    using namespace dot_pp::parser;

    struct NullConstructionPolicy
    {
        void createGraph(const std::string&) {}
        void createDigraph(const std::string&) {}
        
        void createVertex(const std::string&) {}
        void createEdge(const std::string&, const std::string&){}
        
        void applyGraphAttribute(const std::string&, const std::string&){}
        void applyVertexAttribute(const std::string&, const std::string&, const std::string&) {}
        
        void applyEdgeAttribute(const std::string& v1, const std::string& v2, const std::string& attr, const std::string& value)
        {
            edgeAttributes.insert(std::make_pair(std::make_pair(std::make_pair(v1, v2), attr), value));
        }
        
        void finalize() {}
        
        // key: ((v1, v2), attr)
        std::map<std::pair<std::pair<std::string, std::string>, std::string>, std::string> edgeAttributes;
    };
    
    struct ReadAttributeEqualStateFixture
    {
        std::string edgeAttribute(const std::string& v1, const std::string& v2, const std::string& attribute)
        {
            const auto iter = constructor.edgeAttributes.find(std::make_pair(std::make_pair(v1, v2), attribute));
            if(iter != constructor.edgeAttributes.end())
            {
                return iter->second;
            }
            
            throw std::runtime_error("Edge Attribute Key Not Found");
        }
        
        TokenStack attributes;
        TokenStack stack;
        
        NullConstructionPolicy constructor;
        states::ReadAttributeEqualState<NullConstructionPolicy> state;
    };
    
    TEST_FIXTURE(ReadAttributeEqualStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(ReadAttributeEqualStateFixture, verifyTransitionsToReadLeftBracketOnString)
    {
        std::deque<TokenInfo> tokens;
        
        // a -> b -> c -> d [ attribute = value ];
        tokens.emplace_back(Token("a", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("b", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("c", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("d", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("attribute", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("value", TokenType::string), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        
        stack.push(handle++);
        stack.push(handle++);
        stack.push(handle++);
        stack.push(handle++);
        attributes.push(handle++);
        
        CHECK_EQUAL(1U, attributes.size());
        CHECK_EQUAL(4U, stack.size());
        
        CHECK_EQUAL(ParserState::ReadLeftBracket, state.consume(handle++, stack, attributes, constructor));
        
        CHECK_EQUAL(0U, attributes.size());
        CHECK_EQUAL(4U, stack.size());
        
        REQUIRE CHECK_EQUAL(3U, constructor.edgeAttributes.size());
        CHECK_EQUAL("value", edgeAttribute("a", "b", "attribute"));
        CHECK_EQUAL("value", edgeAttribute("b", "c", "attribute"));
        CHECK_EQUAL("value", edgeAttribute("c", "d", "attribute"));
    }

    TEST_FIXTURE(ReadAttributeEqualStateFixture, verifyTransitionsToReadLeftBracketOnStringLiteral)
    {
        std::deque<TokenInfo> tokens;
        
        // a -> b -> c [ attribute = value ];
        tokens.emplace_back(Token("a", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("b", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("c", TokenType::string), FileInfo("test.dot"));
        
        tokens.emplace_back(Token("attribute", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("value", TokenType::string_literal), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        
        stack.push(handle++);
        stack.push(handle++);
        stack.push(handle++);
        attributes.push(handle++);
        
        CHECK_EQUAL(1U, attributes.size());
        CHECK_EQUAL(3U, stack.size());
        
        CHECK_EQUAL(ParserState::ReadLeftBracket, state.consume(handle++, stack, attributes, constructor));
        
        CHECK_EQUAL(0U, attributes.size());
        CHECK_EQUAL(3U, stack.size());
        
        REQUIRE CHECK_EQUAL(2U, constructor.edgeAttributes.size());
        CHECK_EQUAL("value", edgeAttribute("a", "b", "attribute"));
        CHECK_EQUAL("value", edgeAttribute("b", "c", "attribute"));
    }
    
    TEST_FIXTURE(ReadAttributeEqualStateFixture, verifyThrowsOnInvalidTokens)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("keyword", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("directed_edge", TokenType::directed_edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_paren", TokenType::l_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_paren", TokenType::r_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_bracket", TokenType::l_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_bracket", TokenType::r_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token(";", TokenType::end_statement), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah blah", TokenType::comment), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah \n blah", TokenType::multiline_comment), FileInfo("test.dot"));
        
        for(auto handle = tokens.cbegin(), end = tokens.cend(); handle != end; ++handle)
        {
            CHECK_THROW(state.consume(handle, stack, attributes, constructor), dot_pp::SyntaxError);
        }
    }
}
