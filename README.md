# Dot++

A small library for reading DOT graph files and serializing graphs into DOT files. We support a subset of DOT: 

- we don't support subgraphs
- we don't support position attributes 
- we require an semicolon at the end of each line

### Use 

Client code implements a `ConstructionPolicy` to be called into by the DOT parser. The policy is passed to the DOT parser as a template parameter. 

For example:

    class ConstructionPolicy {

        void createGraph(const std::string& name);
        void createDigraph(const std::string& name);

        void createVertex(const std::string& name);
        void createEdge(const std::string& vertex1, const std::string& vertex2);

        void applyGraphAttribute(
              const std::string& attributeName
            , const std::string& value);

        void applyVertexAttribute(
              const std::string& vertex
            , const std::string& attributeName
            , const std::string& value);

        void applyEdgeAttribute(
              const std::string& vertex1
            , const std::string& vertex2
            , const std::string& attributeName
            , const std::string& value);
    };

The implementation of this interface would deal with the specifics of the client's graph library. 

Dot++ provides a `SerializationPolicy` mirroring the `ConstructionPolicy` interface which can be called by client code's graph visitor to serialize a graph into the DOT format. 

### Dependencies 

- c++11
- [UnitTest++](https://github.com/unittest-cpp/unittest-cpp). Unit test framework.

### Contributors 

Austin Gilbert <ceretullis@gmail.com>

### License

4-Clause BSD license, see [LICENSE.md](LICENSE.md) for details. Other licensing available upon request. 
