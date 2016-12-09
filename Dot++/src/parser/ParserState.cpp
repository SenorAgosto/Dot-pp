#include <Dot++/parser/ParserState.hpp>

namespace dot_pp { namespace parser {
    
    std::ostream& operator<<(std::ostream& os, const ParserState state)
    {
        switch(state)
        {
        case ParserState::Init:                     return os << "ParserState::Init";
        case ParserState::GraphKeyword:             return os << "ParserState::GraphKeyword";
        case ParserState::GraphName:                return os << "ParserState::GraphName";
        case ParserState::BeginGraph:               return os << "ParserState::BeginGraph";
        case ParserState::IgnoreSubgraphs:          return os << "ParserState::IgnoreSubgraphs";
        case ParserState::ReadStringToken:          return os << "ParserState::ReadStringToken";
        case ParserState::ReadEdgeToken:            return os << "ParserState::ReadEdgeToken";
        case ParserState::CreatedEdge:              return os << "ParserState::CreateEdge";
        case ParserState::ReadGraphAttributeEqual:  return os << "ParserState::ReadGraphAttributeEqual";
        case ParserState::ReadGraphAttributeValue:  return os << "ParserState::ReadGraphAttributeValue";
        case ParserState::ReadLeftBracketVertexAttribute: return os << "ParserState::ReadLeftBracketVertexAttribute";
        case ParserState::ReadVertexAttributeName:  return os << "ParserState::ReadVertexAttributeName";
        case ParserState::ReadVertexAttributeEqual: return os << "ParserState::ReadVertexAttributeEqual";
        case ParserState::ReadLeftBracket:          return os << "ParserState::ReadLeftBracket";
        case ParserState::ReadAttributeName:        return os << "ParserState::ReadAttributeName";
        case ParserState::ReadAttributeEqual:       return os << "ParserState::ReadAttributeEqual";
        default:                                    return os << "Unknown ParserState Value";
        };
    }
}}
