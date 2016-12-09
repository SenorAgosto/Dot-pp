#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Exceptions.hpp>
#include <Dot++/NullConstructionPolicy.hpp>

#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/parser/states/IgnoreSubgraphsState.hpp>

#include <string> 

namespace {
    
    using namespace dot_pp::lexer;
    using namespace dot_pp::parser;
    
    struct IgnoreSubgraphsStateFixture
    {
        TokenStack attributes;
        TokenStack stack;
        
        dot_pp::NullConstructionPolicy constructor;
        states::IgnoreSubgraphsState<dot_pp::NullConstructionPolicy> state;
    };
    
    TEST_FIXTURE(IgnoreSubgraphsStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(IgnoreSubgraphsStateFixture, verifyIgnoresAllTokensButRightParen)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("comment", TokenType::comment), FileInfo("test.dot"));
        tokens.emplace_back(Token("multiline", TokenType::multiline_comment), FileInfo("test.dot"));
        tokens.emplace_back(Token("string", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("string_lit", TokenType::string_literal), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::directed_edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_bracket", TokenType::l_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_bracket", TokenType::r_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("equal", TokenType::equal), FileInfo("test.dot"));
        tokens.emplace_back(Token("end_statement", TokenType::end_statement), FileInfo("test.dot"));
        tokens.emplace_back(Token("}", TokenType::r_paren), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        
        CHECK_EQUAL(ParserState::IgnoreSubgraphs, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(ParserState::IgnoreSubgraphs, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(ParserState::IgnoreSubgraphs, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(ParserState::IgnoreSubgraphs, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(ParserState::IgnoreSubgraphs, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(ParserState::IgnoreSubgraphs, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(ParserState::IgnoreSubgraphs, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(ParserState::IgnoreSubgraphs, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(ParserState::IgnoreSubgraphs, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(ParserState::IgnoreSubgraphs, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(ParserState::BeginGraph, state.consume(handle++, stack, attributes, constructor));
    }
}
