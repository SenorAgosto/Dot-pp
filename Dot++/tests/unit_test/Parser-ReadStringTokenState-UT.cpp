#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/parser/states/ReadStringTokenState.hpp>

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
    
    struct ReadStringTokenStateFixture
    {
        TokenStack stack;
        NullConstructionPolicy constructor;
        
        states::ReadStringTokenState<NullConstructionPolicy> state;
    };
    
    TEST_FIXTURE(ReadStringTokenStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(ReadStringTokenStateFixture, verifyTransitionsToReadEdgeTokenOnEdge)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("a", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("--", TokenType::edge), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        stack.push(handle++);
        
        CHECK_EQUAL(1U, stack.size());
        CHECK_EQUAL(ParserState::ReadEdgeToken, state.consume(handle++, stack, constructor));
        CHECK_EQUAL(1U, stack.size());
    }

    TEST_FIXTURE(ReadStringTokenStateFixture, verifyTransitionsToReadEdgeTokenOnDirectedEdge)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("a", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("->", TokenType::directed_edge), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        stack.push(handle++);
        
        CHECK_EQUAL(1U, stack.size());
        CHECK_EQUAL(ParserState::ReadEdgeToken, state.consume(handle++, stack, constructor));
        CHECK_EQUAL(1U, stack.size());
    }

    TEST_FIXTURE(ReadStringTokenStateFixture, verifyTransitionsToReadGraphAttributeEqual)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("=", TokenType::equal), FileInfo("test.dot"));

        auto handle = tokens.cbegin();
        
        CHECK_EQUAL(ParserState::ReadGraphAttributeEqual, state.consume(handle++, stack, constructor));
        CHECK_EQUAL(0U, stack.size());
    }
    
    TEST_FIXTURE(ReadStringTokenStateFixture, verifyThrowsOnInvalidTokens)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("keyword", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("string", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("string_lit", TokenType::string_literal), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_paren", TokenType::l_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_paren", TokenType::r_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_bracket", TokenType::l_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_bracket", TokenType::r_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("end_statement", TokenType::end_statement), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah blah", TokenType::comment), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah \n blah", TokenType::multiline_comment), FileInfo("test.dot"));
        
        for(auto handle = tokens.cbegin(), end = tokens.cend(); handle != end; ++handle)
        {
            CHECK_THROW(state.consume(handle, stack, constructor), dot_pp::SyntaxError);
        }
    }
}
