#include "./platform/UnitTestSupport.hpp"
#include <Dot++/Parser.hpp>

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace {
    
    struct GraphMock
    {
        GraphMock()
            : finalized(false)
        {
        }
        
        void createGraph(const std::string& name) { graphName = name.empty() ? "<empty>" : name; }
        void createDigraph(const std::string& name) { digraphName = name.empty() ? "<empty>" : name; }
        
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
        
        void finalize()
        {
            finalized = true;
        }
        
        std::string graphName;
        std::string digraphName;
        
        std::set<std::string> vertices;
        std::set<std::pair<std::string, std::string>> edges;
        
        std::map<std::string, std::string> graphAttributes;
        std::map<std::string, std::pair<std::string, std::string>> vertexAttributes;
        std::map<std::pair<std::string, std::string>, std::pair<std::string, std::string> > edgeAttributes;
        
        bool finalized;
    };
    
    struct ParserFixture
    {
        ParserFixture()
            : parser(graph)
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

        bool hasVertex(const std::set<std::string>& set, const std::string& key)
        {
            return set.find(key) != set.end();
        }
        
        bool hasEdge(const std::set<std::pair<std::string, std::string>>& map, const std::string& v1, const std::string& v2)
        {
            return map.find(std::make_pair(v1, v2)) != map.end();
        }
        
        GraphMock graph;
        dot_pp::Parser<GraphMock> parser;
        
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
    
    TEST_FIXTURE(ParserFixture, verifyConstructsEmptyGraph)
    {
        assertGraphEmpty();
        
        std::istringstream ss("graph {}");
        parser.parse(ss, filename, graph);
        
        CHECK_EQUAL("<empty>", graph.graphName);
        CHECK(graph.vertices.empty());
        CHECK(graph.edges.empty());
    }

    TEST_FIXTURE(ParserFixture, verifyConstructsEmptyDigraph)
    {
        assertGraphEmpty();
        
        std::istringstream ss("digraph {}");
        parser.parse(ss, filename, graph);
        
        CHECK_EQUAL("<empty>", graph.digraphName);
        CHECK(graph.vertices.empty());
        CHECK(graph.edges.empty());
    }
    
    TEST_FIXTURE(ParserFixture, verifyConstructsGraph)
    {
        assertGraphEmpty();
        
        std::istringstream ss(
            "/* This graph contains some\r\n"
            "   some information. \r\n"
            "*/ \n\n"
            "digraph stages {" "\n"
            "\n"
            /*
            "// define vertices with attributes \n"
            "\t" "a [ color=red];"
            "\t" "b [ color = \"blue\"] ;\n"
            "\n"
            */
            "// define some edges...\n"
            "\t" "a -> b -> c -> d -> e [ weight  =  \"1.0\"  ]; \t \r \n"
            "\t" "a -> c -> e  [ weight = 2 ];"
            "\t" "b -> f;" "\n"
            "\t" "{ rank = same; A; B; C;\n"
            "}\r\n");
        
        parser.parse(ss, filename, graph);
        
        CHECK_EQUAL("stages", graph.digraphName);
        
        REQUIRE CHECK_EQUAL(6U, graph.vertices.size());
        CHECK(hasVertex(graph.vertices, "a"));
        CHECK(hasVertex(graph.vertices, "b"));
        CHECK(hasVertex(graph.vertices, "c"));
        CHECK(hasVertex(graph.vertices, "d"));
        CHECK(hasVertex(graph.vertices, "e"));
        CHECK(hasVertex(graph.vertices, "f"));
        
        CHECK_EQUAL(7U, graph.edges.size());
        CHECK(hasEdge(graph.edges, "a", "b"));
        CHECK(hasEdge(graph.edges, "b", "c"));
        CHECK(hasEdge(graph.edges, "c", "d"));
        CHECK(hasEdge(graph.edges, "d", "e"));
        CHECK(hasEdge(graph.edges, "a", "c"));
        CHECK(hasEdge(graph.edges, "c", "e"));
        CHECK(hasEdge(graph.edges, "b", "f"));
    }
}
