#include <Dot++/TokenType.hpp>

namespace dot_pp {

    std::ostream& operator<<(std::ostream& os, const TokenType type)
    {
        switch(type)
        {
        case TokenType::string:                 return os << "TokenType::string";
        case TokenType::string_literal:         return os << "TokenType::string_literal";
        case TokenType::keyword:                return os << "TokenType::keyword";
        case TokenType::l_paren:                return os << "TokenType::l_paren";
        case TokenType::r_paren:                return os << "TokenType::r_paren";
        case TokenType::bidirectional_arrow:    return os << "TokenType::bidirectional_arrow";
        case TokenType::arrow:                  return os << "TokenType::arrow";
        case TokenType::l_bracket:              return os << "TokenType::l_bracket";
        case TokenType::r_bracket:              return os << "TokenType::r_bracket";
        case TokenType::equal:                  return os << "TokenType::equal";
        case TokenType::comment:                return os << "TokenType::comment";
        case TokenType::multiline_comment:      return os << "TokenType::multiline_comment";
        default:                                return os << "Unknown TokenType Value";
        };
    }
}
