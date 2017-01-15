# Dot++

A small library for reading DOT graph files and serializing graphs into DOT files. We support a subset of DOT when parsing: 

- we require an semicolon at the end of each line
- we don't support subgraphs
- we don't support position attributes 
- we will support multiple graphs per input file, your construction policy (see below) should be prepared to deal with that scenario should your input files fall into this catagory. 

### Graph Construction from DOT files 

The DOT parser is parameterized on a client construction policy and calls into the policy as a DOT input is parsed. The following is an example construction policy:

    class ConstructionPolicy {

        void createGraph(const std::string& name);
        void createDigraph(const std::string& name);

        void createVertex(const std::string& name);
        void createEdge(const std::string& vertex1, const std::string& vertex2);

        void applyGraphAttribute(
              const std::string& attributeName
            , const std::string& value);

        void applyDefaultVertexAttribute(
              const std::string& attributeName
            , const std::string& value);

        void applyVertexAttribute(
              const std::string& vertex
            , const std::string& attributeName
            , const std::string& value);

        void applyDefaultEdgeAttribute(
              const std::string& attributeName
            , const std::string& value);

        void applyEdgeAttribute(
              const std::string& vertex1
            , const std::string& vertex2
            , const std::string& attributeName
            , const std::string& value);

        void finalize();
    };

The implementation of this interface deals with the specifics of the client's graph library. This policy should be prepared to handle multiple graphs in the event the input DOT file contains multiple top-level graphs. 

### Graph Serialization 

Dot++ provides a serialization policy which can be called by client code to serialize a graph into the DOT format while visiting the graph using the specifics of the graph library. The serialization policy mirrors the construction policy above - see `Dot++/SerializationPolicy.hpp` for details. 

### Dependencies 

- c++11
- [UnitTest++](https://github.com/unittest-cpp/unittest-cpp). Unit test framework.

### Contributors 

Austin Gilbert <ceretullis@gmail.com>

### License

4-Clause BSD license, see [LICENSE.md](LICENSE.md) for details. Other licensing available upon request. 
