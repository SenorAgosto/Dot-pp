#pragma once 
#include <ostream> 

namespace dot_pp {

    enum class TokenizerState
    {
        Init,
        HashLineComment,
        
        LeftBracket,
        Equal,
        RightBracket,
        
        BeginSlashLineComment,  // first /
        SlashLineComment,       // second /
        
        MultiLineEscape,        // \ at the end of a line
        
        MultiLineComment,       // * after /, e.g. /*
        EndMultiLineComment,    // * before /, e.g. */
        
        StringLiteral,
        StringLiteralEscape,
        
        Error,                  // lexer error leads to error state
    };
    
    std::ostream& operator<<(std::ostream& os, const TokenizerState& state);
}