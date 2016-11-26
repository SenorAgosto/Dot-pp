#include "./platform/UnitTestSupport.hpp"

#include "Dot++/src/states/ProduceToken.hpp"
#include <Dot++/Token.hpp>
#include <Dot++/TokenInfo.hpp>
#include <Dot++/TokenizerState.hpp>

#include <deque> 

namespace {
    
    struct ProduceTokenFixture
    {
        std::deque<dot_pp::Token> tokens;
    };
    
    TEST_FIXTURE(ProduceTokenFixture, verifyProduceTokenWithOneArgument)
    {
        dot_pp::TokenInfo info("test.dot");
        
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(dot_pp::TokenizerState::Init, dot_pp::states::produceToken(dot_pp::TokenizerState::Init, tokens, dot_pp::Token(info)));
        CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, dot_pp::states::produceToken(dot_pp::TokenizerState::Init, tokens, dot_pp::Token(info), dot_pp::Token(info)));
        CHECK_EQUAL(3U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, dot_pp::states::produceToken(dot_pp::TokenizerState::Init, tokens, dot_pp::Token(info), dot_pp::Token(info), dot_pp::Token(info)));
        CHECK_EQUAL(6U, tokens.size());
    }
}
