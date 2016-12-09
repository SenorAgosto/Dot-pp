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
            vertexAttributes.insert(std::make_pair(std::make_pair(vertex, attributeName), value));
        }
        
        void applyEdgeAttribute(const std::string& vertex1, const std::string& vertex2, const std::string& attributeName, const std::string& value)
        {
            edgeAttributes.insert(std::make_pair(std::make_pair(std::make_pair(vertex1, vertex2), attributeName), value));
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
        
        // key: (vertex, attribute)
        std::map<std::pair<std::string, std::string>, std::string> vertexAttributes;
        
        // key: ((v1, v2), attribute)
        std::map<std::pair<std::pair<std::string, std::string>, std::string>, std::string> edgeAttributes;
        
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

        bool hasVertex(const std::string& key)
        {
            return graph.vertices.find(key) != graph.vertices.end();
        }
        
        bool hasEdge(const std::string& v1, const std::string& v2)
        {
            return graph.edges.find(std::make_pair(v1, v2)) != graph.edges.end();
        }
        
        std::string graphAttribute(const std::string& attribute)
        {
            const auto iter = graph.graphAttributes.find(attribute);
            if(iter != graph.graphAttributes.cend())
            {
                return iter->second;
            }
            
            throw std::runtime_error("Graph Attribute Key Not Found");
        }
        
        std::string vertexAttribute(const std::string& vertex, const std::string& attribute)
        {
            const auto iter = graph.vertexAttributes.find(std::make_pair(vertex, attribute));
            if(iter != graph.vertexAttributes.cend())
            {
                return iter->second;
            }
            
            throw std::runtime_error("Vertex Attribute Key Not Found");
        }
        
        std::string edgeAttribute(const std::string& v1, const std::string& v2, const std::string attribute)
        {
            const auto iter = graph.edgeAttributes.find(std::make_pair(std::make_pair(v1, v2), attribute));
            if(iter != graph.edgeAttributes.cend())
            {
                return iter->second;
            }
            
            throw std::runtime_error("Edge Attribute Key Not Found");
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
            "// define graph attribuetes \n"
            "\t" "size = \"100,100\"; \n"
            "\t" "position= center  ; " "\n"
            "// define vertices with attributes \n"
            "\t" "a [ color=red];"
            "\t" "b [ color = \"blue\" weight=3.2] ;\n"
            "\n"
            "// define some edges...\n"
            "\t" "a -> b -> c -> d -> e [ weight  =  \"1.0\" color=red ]; \t \r \n"
            "\t" "a -> c -> e  [ weight = 2 ];"
            "\t" "b -> f;" "\n"
            "\t" "{ rank = same; A; B; C; }\n"
            "}\r\n");
        
        parser.parse(ss, filename, graph);
        
        CHECK_EQUAL("stages", graph.digraphName);
        
        REQUIRE CHECK_EQUAL(6U, graph.vertices.size());
        CHECK(hasVertex("a"));
        CHECK(hasVertex("b"));
        CHECK(hasVertex("c"));
        CHECK(hasVertex("d"));
        CHECK(hasVertex("e"));
        CHECK(hasVertex("f"));
        
        CHECK_EQUAL(7U, graph.edges.size());
        CHECK(hasEdge("a", "b"));
        CHECK(hasEdge("b", "c"));
        CHECK(hasEdge("c", "d"));
        CHECK(hasEdge("d", "e"));
        CHECK(hasEdge("a", "c"));
        CHECK(hasEdge("c", "e"));
        CHECK(hasEdge("b", "f"));
        
        CHECK_EQUAL(2U, graph.graphAttributes.size());
        CHECK_EQUAL("100,100", graphAttribute("size"));
        CHECK_EQUAL("center", graphAttribute("position"));
        
        CHECK_EQUAL(3U, graph.vertexAttributes.size());
        CHECK_EQUAL("red", vertexAttribute("a", "color"));
        CHECK_EQUAL("blue", vertexAttribute("b", "color"));
        CHECK_EQUAL("3.2", vertexAttribute("b", "weight"));
        
        CHECK_EQUAL(10U, graph.edgeAttributes.size());
        CHECK_EQUAL("1.0", edgeAttribute("a", "b", "weight"));
        CHECK_EQUAL("1.0", edgeAttribute("b", "c", "weight"));
        CHECK_EQUAL("1.0", edgeAttribute("c", "d", "weight"));
        CHECK_EQUAL("1.0", edgeAttribute("d", "e", "weight"));

        CHECK_EQUAL("red", edgeAttribute("a", "b", "color"));
        CHECK_EQUAL("red", edgeAttribute("b", "c", "color"));
        CHECK_EQUAL("red", edgeAttribute("c", "d", "color"));
        CHECK_EQUAL("red", edgeAttribute("d", "e", "color"));
        
        CHECK_EQUAL("2", edgeAttribute("a", "c", "weight"));
        CHECK_EQUAL("2", edgeAttribute("c", "e", "weight"));
    }
}
