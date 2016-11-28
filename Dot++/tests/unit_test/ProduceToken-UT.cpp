#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include "Dot++/src/states/ProduceToken.hpp"
#include <Dot++/Token.hpp>
#include <Dot++/TokenizerState.hpp>
#include <Dot++/TokenInfo.hpp>

#include <deque> 

namespace {
    
    struct ProduceTokenFixture
    {
        ProduceTokenFixture()
            : info("test.dot")
        {
        }
        
        dot_pp::FileInfo info;
        dot_pp::Token token;
        std::deque<dot_pp::TokenInfo> tokens;
    };
    
    TEST_FIXTURE(ProduceTokenFixture, verifyProduceTokenWithOneArgument)
    {
        CHECK_EQUAL(0U, tokens.size());
        CHECK_EQUAL(dot_pp::TokenizerState::Init, dot_pp::states::produceToken(dot_pp::TokenizerState::Init, info, tokens, token));
        CHECK_EQUAL(1U, tokens.size());
        
        CHECK_EQUAL(dot_pp::TokenizerState::Init, dot_pp::states::produceToken(dot_pp::TokenizerState::Init, info, tokens, token, dot_pp::Token()));
        CHECK_EQUAL(3U, tokens.size());
    }
}
