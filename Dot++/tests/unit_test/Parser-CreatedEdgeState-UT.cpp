#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/parser/states/CreatedEdgeState.hpp>

#include <string> 

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
        
        void createVertex(const std::string& name) { vertex = name; }
        void createEdge(const std::string&, const std::string&){}
        
        void applyGraphAttribute(const std::string&, const std::string&){}
        void applyVertexAttribute(const std::string&, const std::string&, const std::string&) {}
        
        void applyEdgeAttribute(const std::string&, const std::string&, const std::string&, const std::string&) {}
        void finalize() {}
        
        std::string vertex;
    };
    
    struct CreatedEdgeStateFixture
    {
        TokenStack attributes;
        TokenStack stack;
        
        NullConstructionPolicy constructor;
        states::CreatedEdgeState<NullConstructionPolicy> state;
    };
    
    TEST_FIXTURE(CreatedEdgeStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(CreatedEdgeStateFixture, verifyTransitionsToReadEdgeTokenOnEdge)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("a", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("--", TokenType::edge), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        stack.push(handle++);
        
        CHECK_EQUAL(1U, stack.size());
        CHECK_EQUAL(ParserState::ReadEdgeToken, state.consume(handle++, stack, attributes, constructor));
        
        CHECK_EQUAL(1U, stack.size());
        CHECK(constructor.vertex.empty());
    }

    TEST_FIXTURE(CreatedEdgeStateFixture, verifyTransitionsToReadEdgeTokenOnDirectedEdge)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("a", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("->", TokenType::directed_edge), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        stack.push(handle++);
        
        CHECK_EQUAL(1U, stack.size());
        CHECK_EQUAL(ParserState::ReadEdgeToken, state.consume(handle++, stack, attributes, constructor));
        
        CHECK_EQUAL(1U, stack.size());
        CHECK(constructor.vertex.empty());
    }

    TEST_FIXTURE(CreatedEdgeStateFixture, verifyTransitionsToReadLeftBracketOnLeftBracket)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("a", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("[", TokenType::l_bracket), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        stack.push(handle++);
        
        CHECK_EQUAL(1U, stack.size());
        CHECK_EQUAL(ParserState::ReadLeftBracket, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(1U, stack.size());
    }
    
    TEST_FIXTURE(CreatedEdgeStateFixture, verifyTransitionsToBeginGraphOnEndStatement)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("a", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token(";", TokenType::end_statement), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        stack.push(handle++);
        
        CHECK_EQUAL(1U, stack.size());
        CHECK_EQUAL(ParserState::BeginGraph, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(0U, stack.size());
    }
    
    TEST_FIXTURE(CreatedEdgeStateFixture, verifyThrowsOnInvalidTokens)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("keyword", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("string", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("string_lit", TokenType::string_literal), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_paren", TokenType::l_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_paren", TokenType::r_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_bracket", TokenType::r_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah blah", TokenType::comment), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah \n blah", TokenType::multiline_comment), FileInfo("test.dot"));
        
        for(auto handle = tokens.cbegin(), end = tokens.cend(); handle != end; ++handle)
        {
            CHECK_THROW(state.consume(handle, stack, attributes, constructor), dot_pp::SyntaxError);
        }
    }
}
