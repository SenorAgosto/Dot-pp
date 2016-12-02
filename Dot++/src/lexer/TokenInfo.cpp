#include <Dot++/lexer/TokenInfo.hpp>

namespace dot_pp { namespace lexer {

    TokenInfo::TokenInfo(const Token& token, const FileInfo& info)
        : fileInfo_(info)
        , token_(token)
    {
    }
}}
