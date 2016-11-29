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
        edge,                   // --
        directed_edge,          // ->

        l_bracket,              // [
        r_bracket,              // ]
        equal,                  // =
        end_statement,          // ;
        
        comment,
        multiline_comment,
    };
    
    std::ostream& operator<<(std::ostream& os, const TokenType type);
}
