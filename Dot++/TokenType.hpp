#pragma once 
#include <cstdint>
#include <ostream>

namespace dot_pp {

    enum class TokenType : uint8_t {
        string,
        string_literal,
        
        keyword,                // graph | digraph
        
        l_paren,                // {
        r_paren,                // }
        bidirectional_arrow,    // --
        arrow,                  // ->

        l_bracket,              // [
        r_bracket,              // ]
        equal,                  // =
        
        comment,
        multiline_comment,
    };
    
    std::ostream& operator<<(std::ostream& os, const TokenType type);
}
