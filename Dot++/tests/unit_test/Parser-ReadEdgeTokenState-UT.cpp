#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/parser/states/ReadEdgeTokenState.hpp>

#include <string> 
#include <utility>

namespace {
    
    using namespace dot_pp::lexer;
    using namespace dot_pp::parser;

    struct NullConstructionPolicy
    {
        void createGraph(const std::string&) {}
        void createDigraph(const std::string&) {}
        
        void createVertex(const std::string& name) { vertex = name; }
        void createEdge(const std::string& v1, const std::string& v2){ edge = std::make_pair(v1, v2); }
        
        void applyGraphAttribute(const std::string&, const std::string&){}
        void applyVertexAttribute(const std::string&, const std::string&, const std::string&) {}
        
        void applyEdgeAttribute(const std::string&, const std::string&, const std::string&, const std::string&) {}
        void finalize() {}
        
        std::pair<std::string, std::string> edge;
        std::string vertex;
    };
    
    struct ReadEdgeTokenStateFixture
    {
        TokenStack stack;
        NullConstructionPolicy constructor;
        
        states::ReadEdgeTokenState<NullConstructionPolicy> state;
    };
    
    TEST_FIXTURE(ReadEdgeTokenStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(ReadEdgeTokenStateFixture, verifyTransitionsToCreatedEdgeTokenOnEdge)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("a", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("b", TokenType::string), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        stack.push(handle++);
        
        CHECK_EQUAL(1U, stack.size());
        CHECK_EQUAL(ParserState::CreatedEdge, state.consume(handle++, stack, constructor));
        CHECK_EQUAL(2U, stack.size());  // both vertices should be on the stack after edge
        
        CHECK_EQUAL("b", constructor.vertex);
        CHECK_EQUAL("a", constructor.edge.first);
        CHECK_EQUAL("b", constructor.edge.second);
    }
    
    TEST_FIXTURE(ReadEdgeTokenStateFixture, verifyThrowsOnInvalidTokens)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("keyword", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("string_lit", TokenType::string_literal), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_paren", TokenType::l_paren), FileInfo("test.dot"));
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
            CHECK_THROW(state.consume(handle, stack, constructor), dot_pp::SyntaxError);
        }
    }
}
