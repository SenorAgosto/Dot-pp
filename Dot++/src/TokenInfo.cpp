#include <Dot++/TokenInfo.hpp>

namespace dot_pp {

    TokenInfo::TokenInfo(const Token& token, const FileInfo& info)
        : fileInfo_(info)
        , token_(token)
    {
    }
}
