#include <Dot++/TokenType.hpp>

namespace dot_pp {

    std::ostream& operator<<(std::ostream& os, const TokenType type)
    {
        switch(type)
        {
        case TokenType::string:                 os << "TokenType::string";
        case TokenType::string_literal:         os << "TokenType::string_literal";
        case TokenType::keyword:                os << "TokenType::keyword";
        case TokenType::l_paren:                os << "TokenType::l_paren";
        case TokenType::r_paren:                os << "TokenType::r_paren";
        case TokenType::bidirectional_arrow:    os << "TokenType::bidirectional_arrow";
        case TokenType::arrow:                  os << "TokenType::arrow";
        case TokenType::l_bracket:              os << "TokenType::l_bracket";
        case TokenType::r_bracket:              os << "TokenType::r_bracket";
        case TokenType::equal:                  os << "TokenType::equal";
        case TokenType::comment:                os << "TokenType::comment";
        case TokenType::multiline_comment:      os << "TokenType::multiline_comment";
        default:                                os << "Unknown TokenType Value";
        };
        
        return os;
    }
}
