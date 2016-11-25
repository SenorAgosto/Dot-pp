#include "./platform/UnitTestSupport.hpp"

#include "Dot++/src/states/ProduceToken.hpp"
#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>

#include <deque> 

namespace {
    
    struct ProduceTokenFixture
    {
        std::deque<dot_pp::Token> tokens;
    };
    
    TEST_FIXTURE(ProduceTokenFixture, verifyProduceTokenWithOneArgument)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(dot_pp::TokenizerState::Init, dot_pp::produceToken(dot_pp::TokenizerState::Init, tokens, dot_pp::Token()));
        CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, dot_pp::produceToken(dot_pp::TokenizerState::Init, tokens, dot_pp::Token(), dot_pp::Token()));
        CHECK_EQUAL(3U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, dot_pp::produceToken(dot_pp::TokenizerState::Init, tokens, dot_pp::Token(), dot_pp::Token(), dot_pp::Token()));
        CHECK_EQUAL(6U, tokens.size());
    }
}
