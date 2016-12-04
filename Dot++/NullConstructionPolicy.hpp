#pragma once 
#include <string> 

struct NullConstructionPolicy
{
    void createGraph(const std::string&) {}
    void createDigraph(const std::string&) {}
    
    void createVertex(const std::string&) {}
    void createEdge(const std::string&, const std::string&){}
    
    void applyGraphAttribute(const std::string&, const std::string&){}
    void applyVertexAttribute(const std::string&, const std::string&, const std::string&) {}
    
    void applyEdgeAttribute(const std::string&, const std::string&, const std::string&, const std::string&) {}
};
