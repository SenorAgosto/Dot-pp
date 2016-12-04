#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/parser/states/GraphNameState.hpp>

#include <string> 

namespace {
    
    using namespace dot_pp::lexer;
    using namespace dot_pp::parser;
    
    struct NullConstructionPolicy
    {
        void createGraph(const std::string& name) { graphName = name; }
        void createDigraph(const std::string& name) { digraphName = name; }
        
        void createVertex(const std::string&) {}
        void createEdge(const std::string&, const std::string&){}
        
        void applyGraphAttribute(const std::string&, const std::string&){}
        void applyVertexAttribute(const std::string&, const std::string&, const std::string&) {}
        
        void applyEdgeAttribute(const std::string&, const std::string&, const std::string&, const std::string&) {}
        
        std::string graphName;
        std::string digraphName;
    };
    
    struct GraphNameStateFixture
    {
        TokenStack stack;
        NullConstructionPolicy constructor;
        
        states::GraphNameState<NullConstructionPolicy> state;
    };
    
    TEST_FIXTURE(GraphNameStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(GraphNameStateFixture, verifyCreatesGraphAndTransitionsToGraphNameStateOnStringToken)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("graph", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("stages", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("{", TokenType::l_paren), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        stack.push(handle++);
        stack.push(handle++);
        
        handle = tokens.cbegin();
        std::advance(handle, 2);
        
        CHECK_EQUAL(ParserState::BeginGraph, state.consume(handle, stack, constructor));
        CHECK_EQUAL("stages", constructor.graphName);
        CHECK_EQUAL(0U, stack.size());
    }
    
    TEST_FIXTURE(GraphNameStateFixture, verifyCreatesDigraphAndTransitionsToGraphNameStateOnStringToken)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("digraph", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("stages", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("{", TokenType::l_paren), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        stack.push(handle++);
        stack.push(handle++);
        
        handle = tokens.cbegin();
        std::advance(handle, 2);
        
        CHECK_EQUAL(ParserState::BeginGraph, state.consume(handle, stack, constructor));
        CHECK_EQUAL("stages", constructor.digraphName);
        CHECK_EQUAL(0U, stack.size());
    }
    
    TEST_FIXTURE(GraphNameStateFixture, verifyCommentsAreIgnored)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("blah blah", TokenType::comment), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah \n blah", TokenType::multiline_comment), FileInfo("test.dot"));

        auto handle = tokens.cbegin();
        CHECK_EQUAL(ParserState::GraphName, state.consume(handle++, stack, constructor));
        CHECK_EQUAL(0U, stack.size());
        
        CHECK_EQUAL(ParserState::GraphName, state.consume(handle++, stack, constructor));
        CHECK_EQUAL(0U, stack.size());
    }
    
    TEST_FIXTURE(GraphNameStateFixture, verifyThrowsOnInvalidToken)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("string", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("string_lit", TokenType::string_literal), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_paren", TokenType::r_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::directed_edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_bracket", TokenType::l_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_bracket", TokenType::r_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("equal", TokenType::equal), FileInfo("test.dot"));
        tokens.emplace_back(Token("end_statement", TokenType::end_statement), FileInfo("test.dot"));
        
        for(auto handle = tokens.cbegin(), end = tokens.cend(); handle != end; ++handle)
        {
            CHECK_THROW(state.consume(handle, stack, constructor), dot_pp::SyntaxError);
        }
    }
}
