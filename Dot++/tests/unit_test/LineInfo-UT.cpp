#include "./platform/UnitTestSupport.hpp"
#include <Dot++/LineInfo.hpp>

namespace {

    struct LineInfoFixture
    {
        LineInfoFixture()
            : li2(100, 20)
        {
        }
        
        dot_pp::LineInfo li;
        dot_pp::LineInfo li2;
    };
    
    TEST_FIXTURE(LineInfoFixture, verifyInstantation)
    {
        CHECK_EQUAL(1U, li.line());
        CHECK_EQUAL(1U, li.column());
        
        CHECK_EQUAL(100U, li2.line());
        CHECK_EQUAL(20U, li2.column());
    }
    
    TEST_FIXTURE(LineInfoFixture, verifyLessThan)
    {
        CHECK(li < li2);
    }
    
    TEST_FIXTURE(LineInfoFixture, verifyEqual)
    {
        dot_pp::LineInfo li3;
        CHECK(li == li3);
    }
    
    TEST_FIXTURE(LineInfoFixture, verifyGreaterThan)
    {
        CHECK(li2 > li);
    }
}
