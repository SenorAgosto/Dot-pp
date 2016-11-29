#include "./platform/UnitTestSupport.hpp"

#include <Dot++/FileInfo.hpp>
#include <Dot++/LineInfo.hpp>
#include <Dot++/Token.hpp>
#include <Dot++/TokenType.hpp>

namespace {

    struct FileInfoFixture
    {
        FileInfoFixture()
            : start(100, 42)
            , end(100, 50)
            , info("test.dot", start, end)
        {
        }
        
        dot_pp::LineInfo start;
        dot_pp::LineInfo end;
        dot_pp::FileInfo info;
    };

    TEST(verifyConstructionWithFilenameOnly)
    {
        dot_pp::FileInfo info("test.dot");
        dot_pp::LineInfo line;
        
        CHECK_EQUAL("test.dot", info.filename());
        CHECK_EQUAL(line, info.start());
        CHECK_EQUAL(line, info.end());
    }
    
    TEST(verifyConstructionWithFilenameAndStart)
    {
        dot_pp::LineInfo line(100, 42);
        dot_pp::FileInfo info("test.dot", line);
        
        CHECK_EQUAL("test.dot", info.filename());
        CHECK_EQUAL(line, info.start());
        CHECK_EQUAL(line, info.end());
    }
    
    TEST(verifyConstructionWithAllParams)
    {
        dot_pp::LineInfo start(100, 42);
        dot_pp::LineInfo end(100, 50);
        dot_pp::FileInfo info("test.dot", start, end);
        
        CHECK_EQUAL("test.dot", info.filename());
        CHECK_EQUAL(start, info.start());
        CHECK_EQUAL(end, info.end());
    }
    
    TEST(verifyCopyConstruction)
    {
        dot_pp::LineInfo start(100, 42);
        dot_pp::LineInfo end(100, 50);
        dot_pp::FileInfo info("test.dot", start, end);
        
        CHECK_EQUAL("test.dot", info.filename());
        CHECK_EQUAL(start, info.start());
        CHECK_EQUAL(end, info.end());

        dot_pp::FileInfo info2(info);

        CHECK_EQUAL("test.dot", info2.filename());
        CHECK_EQUAL(start, info2.start());
        CHECK_EQUAL(end, info2.end());
    }
    
    TEST(verifyMoveConstruction)
    {
        dot_pp::LineInfo start(100, 42);
        dot_pp::LineInfo end(100, 50);
        dot_pp::FileInfo info(dot_pp::FileInfo("test.dot", start, end));
        
        CHECK_EQUAL("test.dot", info.filename());
        CHECK_EQUAL(start, info.start());
        CHECK_EQUAL(end, info.end());
    }
    
    TEST_FIXTURE(FileInfoFixture, verifyIncrementLine)
    {
        CHECK_EQUAL(end, info.end());
        
        info.incrementLine();
        CHECK_EQUAL(end.line() + 1, info.end().line());
        CHECK_EQUAL(1U, info.end().column());
    }
    
    TEST_FIXTURE(FileInfoFixture, verifyIncrementColumn)
    {
        CHECK_EQUAL(end, info.end());
        
        info.incrementColumn();
        CHECK_EQUAL(end.line(), info.end().line());
        CHECK_EQUAL(end.column() + 1, info.end().column());
    }
    
    TEST_FIXTURE(FileInfoFixture, verifyIncrementColumnByValue)
    {
        CHECK_EQUAL(end, info.end());
        
        info.incrementColumnBy(4);
        CHECK_EQUAL(end.line(), info.end().line());
        CHECK_EQUAL(end.column() + 4, info.end().column());
    }
    
    TEST_FIXTURE(FileInfoFixture, verifyAdvanceBy)
    {
        dot_pp::Token token("variable20", dot_pp::TokenType::string);
        
        CHECK_EQUAL(end, info.end());
        
        info.advanceBy(token);
        CHECK_EQUAL(end.line(), info.end().line());
        CHECK_EQUAL(end.column() + 10, info.end().column());
    }
    
    TEST_FIXTURE(FileInfoFixture, verifyAdvanceByWithEmbededNewLines)
    {
        dot_pp::Token token("variable20\nvariable21\nvariable22", dot_pp::TokenType::multiline_comment);
        
        CHECK_EQUAL(end, info.end());
        
        info.advanceBy(token);
        CHECK_EQUAL(end.line() + 2, info.end().line());
        CHECK_EQUAL(11U, info.end().column());
    }
    
    TEST_FIXTURE(FileInfoFixture, verifyEmpty)
    {
        dot_pp::LineInfo empty;
        dot_pp::FileInfo info2("test.dot", empty, empty);
        
        CHECK(!info.empty());
        CHECK(info2.empty());
    }
}
