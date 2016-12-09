#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/parser/states/GraphKeywordState.hpp>

namespace {
    
    using namespace dot_pp::lexer;
    using namespace dot_pp::parser;

    struct NullConstructionPolicy
    {
        NullConstructionPolicy()
            : madeGraph(false)
            , madeDigraph(false)
        {
        }
        
        void createGraph(const std::string&) { madeGraph = true; }
        void createDigraph(const std::string&) { madeDigraph = true; }
        
        void createVertex(const std::string&) {}
        void createEdge(const std::string&, const std::string&){}
        
        void applyGraphAttribute(const std::string&, const std::string&){}
        void applyVertexAttribute(const std::string&, const std::string&, const std::string&) {}
        
        void applyEdgeAttribute(const std::string&, const std::string&, const std::string&, const std::string&) {}
        
        bool madeGraph;
        bool madeDigraph;
    };
    
    struct GraphKeywordStateFixture
    {
        TokenStack attributes;
        TokenStack stack;
        
        NullConstructionPolicy constructor;
        states::GraphKeywordState<NullConstructionPolicy> state;
    };
    
    TEST_FIXTURE(GraphKeywordStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(GraphKeywordStateFixture, verifyTransitionsToGraphNameStateOnStringToken)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("stages", TokenType::string), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        CHECK_EQUAL(ParserState::GraphName, state.consume(handle, stack, attributes, constructor));
    }
    
    TEST_FIXTURE(GraphKeywordStateFixture, verifyCreatesGraphAndTransitionsToBeginGraphOnLeftParen)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("graph", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("{", TokenType::l_paren), FileInfo("test.dot"));
     
        auto handle = tokens.cbegin();
        stack.push(handle++);

        CHECK_EQUAL(ParserState::BeginGraph, state.consume(handle, stack, attributes, constructor));
        CHECK(constructor.madeGraph);
    }

    TEST_FIXTURE(GraphKeywordStateFixture, verifyCreatesDigraphAndTransitionsToBeginGraphOnLeftParen)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("digraph", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("{", TokenType::l_paren), FileInfo("test.dot"));

        auto handle = tokens.cbegin();
        stack.push(handle++);

        CHECK_EQUAL(ParserState::BeginGraph, state.consume(handle, stack, attributes, constructor));
        CHECK(constructor.madeDigraph);
    }
    
    TEST_FIXTURE(GraphKeywordStateFixture, verifyThrowsOnInvalidGraphKeyword)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("invalid", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("{", TokenType::l_paren), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        stack.push(handle++);

        CHECK_THROW(state.consume(handle, stack, attributes, constructor), dot_pp::SyntaxError);
    }
    
    TEST_FIXTURE(GraphKeywordStateFixture, verifySyntaxErrorOnOtherTokenTypes)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("keyword", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("string_lit", TokenType::string_literal), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_paren", TokenType::r_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::directed_edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_bracket", TokenType::l_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_bracket", TokenType::r_bracket), FileInfo("test.dot"));
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
