#include "./platform/UnitTestSupport.hpp"
#include <Dot++/Parser.hpp>

#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace {
    
    struct LoggingInterface
    {
        static void info(const std::string&) {}
        static void warn(const std::string&) {}
        static void error(const std::string&) {}
    };
    
    struct GraphMock
    {
        void createGraph(const std::string& name) { graphName = name; }
        void createDigraph(const std::string& name) { digraphName = name; }
        
        void createVertex(const std::string& name) { vertices.insert(name); }
        void createEdge(const std::string& vertex1, const std::string& vertex2)
        {
            edges.insert(std::make_pair(vertex1, vertex2));
        }
        
        void applyGraphAttribute(const std::string& attributeName, const std::string& value)
        {
            graphAttributes.insert(std::make_pair(attributeName, value));
        }
        
        void applyVertexAttribute(const std::string& vertex, const std::string& attributeName, const std::string& value)
        {
            vertexAttributes.insert(std::make_pair(vertex, std::make_pair(attributeName, value)));
        }
        
        void applyEdgeAttribute(const std::string& vertex1, const std::string& vertex2, const std::string& attributeName, const std::string& value)
        {
            edgeAttributes.insert(std::make_pair(std::make_pair(vertex1, vertex2), std::make_pair(attributeName, value)));
        }
        
        std::string graphName;
        std::string digraphName;
        
        std::set<std::string> vertices;
        std::map<std::string, std::string> edges;
        
        std::map<std::string, std::string> graphAttributes;
        std::map<std::string, std::pair<std::string, std::string>> vertexAttributes;
        std::map<std::pair<std::string, std::string>, std::pair<std::string, std::string> > edgeAttributes;
    };
    
    struct ParserFixture
    {
        ParserFixture()
            : parser(logHandle)
            , filename("test.dot")
        {
        }
        
        void assertGraphEmpty()
        {
            CHECK(graph.graphName.empty());
            CHECK(graph.digraphName.empty());
            CHECK(graph.vertices.empty());
            CHECK(graph.edges.empty());
            CHECK(graph.graphAttributes.empty());
            CHECK(graph.vertexAttributes.empty());
            CHECK(graph.edgeAttributes.empty());
        }
        
        GraphMock graph;
        LoggingInterface logHandle;
        dot_pp::Parser<GraphMock, LoggingInterface> parser;
        
        const std::string filename;
    };

    TEST_FIXTURE(ParserFixture, verifyInstantiation)
    {
    }
    
    TEST_FIXTURE(ParserFixture, verifyIgnoresWhitespace)
    {
        assertGraphEmpty();
        
        std::istringstream ss(" \t\n");
        parser.parse(ss, filename, graph);
        
        assertGraphEmpty();
    }
}
