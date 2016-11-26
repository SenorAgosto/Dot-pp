#include <Dot++/TokenizerStatesPack.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/TokenizerState.hpp>

namespace dot_pp {

    const TokenizerStateInterface& TokenizerStatesPack::operator[](const TokenizerState state) const
    {
        // ordered by frequency of use
        switch(state)
        {
        case TokenizerState::Init:                      return init_;
        case TokenizerState::StringLiteral:             return stringLiteral_;
        case TokenizerState::StringLiteralEscape:       return stringLiteralEscape_;
        
        case TokenizerState::HashLineComment:           return hashLineComment_;
                
        case TokenizerState::BeginSlashLineComment:     return beginSlashLine_;
        case TokenizerState::SlashLineComment:          return slashLineComment_;
                
        case TokenizerState::MultiLineComment:          return multiLineComment_;
        case TokenizerState::EndMultiLineComment:       return endMultiLineComment_;
        case TokenizerState::MultiLineEscape:           return multiLineEscape_;
        
        case TokenizerState::Error:                     return error_;

        default: break;
        };
        
        throw UnknownTokenizerState(state);
    }
}
