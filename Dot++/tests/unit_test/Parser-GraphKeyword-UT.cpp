#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/parser/states/GraphKeywordState.hpp>

namespace {
    
    using namespace dot_pp::lexer;
    using namespace dot_pp::parser;
    
    struct GraphKeywordStateFixture
    {
        TokenStack stack;
        states::GraphKeywordState state;
    };
    
    TEST_FIXTURE(GraphKeywordStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(GraphKeywordStateFixture, verifyTransitionsToGraphNameStateOnStringToken)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("stages", TokenType::string), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        CHECK_EQUAL(ParserState::GraphName, state.consume(handle, stack));
    }
    
    TEST_FIXTURE(GraphKeywordStateFixture, verifyTransitionsToBeginGraphOnLeftParen)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("{", TokenType::l_paren), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        CHECK_EQUAL(ParserState::BeginGraph, state.consume(handle, stack));
    }
    
    TEST_FIXTURE(GraphKeywordStateFixture, verifySyntaxErrorOnOtherTokenTypes)
    {
        std::deque<TokenInfo> tokens;
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
            CHECK_THROW(state.consume(handle, stack), dot_pp::SyntaxError);
        }
    }
}
