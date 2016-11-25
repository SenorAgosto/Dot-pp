#include <Dot++/TokenizerState.hpp>

namespace dot_pp {
    
    std::ostream& operator<<(std::ostream& os, const TokenizerState& state)
    {
        switch(state)
        {
        case TokenizerState::Init:                      os << "TokenizerState::Init"; break;
        case TokenizerState::HashLineComment:           os << "TokenizerState::HashLineComment"; break;
        case TokenizerState::BeginSlashLineComment:     os << "TokenizerState::BeginSlashLineComment"; break;
        case TokenizerState::SlashLineComment:          os << "TokenizerState::SlashLineComment"; break;
        case TokenizerState::MultiLineEscape:           os << "TokenizerState::MultiLineEscape"; break;
        case TokenizerState::MultiLineComment:          os << "TokenizerState::MultiLineComment"; break;
        case TokenizerState::EndMultiLineComment:       os << "TokenizerState::EndMultiLineComment"; break;
        case TokenizerState::StringLiteral:             os << "TokenizerState::StringLiteral"; break;
        case TokenizerState::StringLiteralEscape:       os << "TokenizerState::StringLiteralEscape"; break;
        case TokenizerState::Error:                     os << "TokenizerState::Error"; break;
        default:                                        os << "Unknown"; break;
        };
        
        return os;
    }
}
