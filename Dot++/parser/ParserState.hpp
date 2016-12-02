#pragma once 
#include <ostream>

namespace dot_pp { namespace parser {
    
    enum class ParserState
    {
        Init,
        
        GraphKeyword,               // digraph | graph
        GraphName,                  // string graph name
        BeginGraph,                 // {
        
        IgnoreSubgraphs,            // any { after the initial graph begins until } ends graph
        
        ReadStringToken,            // push string token
        ReadEdgeToken,              // edge | directed_edge, pop string token, create vertex, push string token
        CreateEdge,                 // create vertex, pop token, create edge, push edge vertex1, push edge vertex2
        
        ReadGraphAttributeEqual,    // =
        ReadGraphAttributeValue,    // string | string_literal token, pop token, create graph attribute
        
        ReadRightBracket,           // [
        ReadAttributeName,          // push string token
        ReadAttributeEqual,         // pop token, create adge attribute
    };
    
    std::ostream& operator<<(std::ostream& os, const ParserState state);
}}
