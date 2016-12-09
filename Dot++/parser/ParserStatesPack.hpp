#pragma once 

#include <Dot++/parser/ParserState.hpp>
#include <Dot++/parser/TokenInfoHandle.hpp>
#include <Dot++/parser/TokenStack.hpp>

#include <Dot++/parser/states/BeginGraphState.hpp>
#include <Dot++/parser/states/CreatedEdgeState.hpp>
#include <Dot++/parser/states/GraphKeywordState.hpp>
#include <Dot++/parser/states/GraphNameState.hpp>
#include <Dot++/parser/states/IgnoreSubgraphsState.hpp>
#include <Dot++/parser/states/InitialState.hpp>
#include <Dot++/parser/states/ReadAttributeEqualState.hpp>
#include <Dot++/parser/states/ReadAttributeNameState.hpp>
#include <Dot++/parser/states/ReadEdgeTokenState.hpp>
#include <Dot++/parser/states/ReadGraphAttributeEqualState.hpp>
#include <Dot++/parser/states/ReadGraphAttributeValueState.hpp>
#include <Dot++/parser/states/ReadLeftBracketState.hpp>
#include <Dot++/parser/states/ReadLeftBracketVertexAttributeState.hpp>
#include <Dot++/parser/states/ReadStringTokenState.hpp>
#include <Dot++/parser/states/ReadVertexAttributeNameState.hpp>
#include <Dot++/parser/states/ReadVertexAttributeEqualState.hpp>

namespace dot_pp { namespace parser {
    
    template<class ConstructionPolicy>
    class ParserStatesPack
    {
    public:
        ParserState consume(const ParserState state, const TokenInfoHandle& token, TokenStack& stack, ConstructionPolicy& constructor)
        {
            switch(state)
            {
            case ParserState::Init:                         return init_.consume(token, stack, constructor);
            case ParserState::GraphKeyword:                 return graphKeyword_.consume(token, stack, constructor);
            case ParserState::GraphName:                    return graphName_.consume(token, stack, constructor);
            case ParserState::BeginGraph:                   return begin_.consume(token, stack, constructor);
            case ParserState::IgnoreSubgraphs:              return ignoreSubgraphs_.consume(token, stack, constructor);
            case ParserState::ReadStringToken:              return readStringToken_.consume(token, stack, constructor);
            case ParserState::ReadEdgeToken:                return readEdgeToken_.consume(token, stack, constructor);
            case ParserState::CreatedEdge:                  return createEdge_.consume(token, stack, constructor);
            case ParserState::ReadGraphAttributeEqual:      return readGraphAttributeEqual_.consume(token, stack, constructor);
            case ParserState::ReadGraphAttributeValue:      return readGraphAttributeValue_.consume(token, stack, constructor);
            case ParserState::ReadLeftBracketVertexAttribute: return leftBracketVertexAttribute_.consume(token, stack, constructor);
            case ParserState::ReadVertexAttributeName:      return vertexAttributeName_.consume(token, stack, constructor);
            case ParserState::ReadVertexAttributeEqual:     return vertexAttributeEqual_.consume(token, stack, constructor);
            case ParserState::ReadLeftBracket:              return readLeftBracket_.consume(token, stack, constructor);
            case ParserState::ReadAttributeName:            return readAttributeName_.consume(token, stack, constructor);
            case ParserState::ReadAttributeEqual:           return readAttributeEqual_.consume(token, stack, constructor);
            default: break;
            };
            
            throw UnknownParserState(state);
        }
        
    private:
        states::InitialState<ConstructionPolicy> init_;
        
        states::GraphKeywordState<ConstructionPolicy> graphKeyword_;
        states::GraphNameState<ConstructionPolicy> graphName_;
        states::BeginGraphState<ConstructionPolicy> begin_;
        
        states::ReadStringTokenState<ConstructionPolicy> readStringToken_;
        states::ReadEdgeTokenState<ConstructionPolicy> readEdgeToken_;
        states::CreatedEdgeState<ConstructionPolicy> createEdge_;
        
        states::ReadAttributeEqualState<ConstructionPolicy> readAttributeEqual_;
        states::ReadAttributeNameState<ConstructionPolicy> readAttributeName_;
        states::ReadLeftBracketState<ConstructionPolicy> readLeftBracket_;
        
        states::ReadGraphAttributeEqualState<ConstructionPolicy> readGraphAttributeEqual_;
        states::ReadGraphAttributeValueState<ConstructionPolicy> readGraphAttributeValue_;
        
        states::ReadLeftBracketVertexAttributeState<ConstructionPolicy> leftBracketVertexAttribute_;
        states::ReadVertexAttributeNameState<ConstructionPolicy> vertexAttributeName_;
        states::ReadVertexAttributeEqualState<ConstructionPolicy> vertexAttributeEqual_;
        
        states::IgnoreSubgraphsState<ConstructionPolicy> ignoreSubgraphs_;
    };
}}

