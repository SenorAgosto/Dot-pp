#pragma once 
#include <ostream>
#include <string>

namespace dot_pp {

    class SerializationPolicy
    {
    public:
        SerializationPolicy(std::ostream& stream);
        
        void createGraph(const std::string& name = "");
        void createDigraph(const std::string& name = "");
        
        void createVertex(const std::string& name);
        void createVertex(const std::string& name, const std::string& attributeName, const std::string& value);
        
        void createEdge(const std::string& vertex1, const std::string& vertex2);
        void createEdge(const std::string& vertex1, const std::string& vertex2, const std::string& attributeName, const std::string& value);
        
        void applyGraphAttribute(const std::string& attributeName, const std::string& value);

        void finalize();
        
    private:
        std::ostream& stream_;
        std::string edgeStyle_;
    };
}
