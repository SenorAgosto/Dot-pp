#include <Dot++/SerializationPolicy.hpp>

namespace dot_pp {
    
    SerializationPolicy::SerializationPolicy(std::ostream& stream)
        : stream_(stream)
        , edgeStyle_("--")
    {
    }
            
    void SerializationPolicy::createGraph(const std::string& name)
    {
        stream_ << "graph " << name << (name.empty() ? "" : " ") << "{\n";
    }
    
    void SerializationPolicy::createDigraph(const std::string& name)
    {
        edgeStyle_ = "->";
        stream_ << "digraph " << name << (name.empty() ? "" : " ") << "{\n";
    }
    
    void SerializationPolicy::createVertex(const std::string&)
    {
    }

    void SerializationPolicy::createVertex(const std::string& vertex, const std::string& attributeName, const std::string& value)
    {
        stream_ << "\t" << vertex << " [" << attributeName << "=" << value << "];\n";
    }

    void SerializationPolicy::createEdge(const std::string& vertex1, const std::string& vertex2)
    {
        stream_ << "\t" << vertex1 << " " << edgeStyle_ << " " << vertex2 << ";\n";
    }
    
    void SerializationPolicy::applyGraphAttribute(const std::string& attributeName, const std::string& value)
    {
        stream_ << "\t" << attributeName << "=" << value << ";\n";
    }
    
    void SerializationPolicy::createEdge(const std::string& vertex1, const std::string& vertex2, const std::string& attributeName, const std::string& value)
    {
        stream_ << "\t" << vertex1 << " " << edgeStyle_ << " " << vertex2 << " [" << attributeName << "=" << value << "];\n";
    }
    
    void SerializationPolicy::finalize()
    {
        stream_ << "}" << std::endl;
    }
}
