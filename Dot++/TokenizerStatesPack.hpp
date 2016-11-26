#pragma once

#include <Dot++/states/InitialState.hpp>
#include <Dot++/states/BeginSlashLineCommentState.hpp>
#include <Dot++/states/EndMultiLineCommentState.hpp>
#include <Dot++/states/ErrorState.hpp>
#include <Dot++/states/HashLineCommentState.hpp>
#include <Dot++/states/InitialState.hpp>
#include <Dot++/states/MultiLineCommentState.hpp>
#include <Dot++/states/MultiLineEscapeState.hpp>
#include <Dot++/states/SlashLineCommentState.hpp>
#include <Dot++/states/StringLiteralEscapeState.hpp>
#include <Dot++/states/StringLiteralState.hpp>

namespace dot_pp {
    enum class TokenizerState;
    class TokenizerStateInterface;
}

namespace dot_pp {
    
    class TokenizerStatesPack
    {
    public:
        const TokenizerStateInterface& operator[](const TokenizerState state) const;

    private:
        states::InitialState init_;
        states::BeginSlashLineCommentState beginSlashLine_;
        states::EndMultiLineCommentState endMultiLineComment_;
        states::HashLineCommentState hashLineComment_;
        states::MultiLineCommentState multiLineComment_;
        states::MultiLineEscapeState multiLineEscape_;
        states::SlashLineCommentState slashLineComment_;
        states::StringLiteralState stringLiteral_;
        states::StringLiteralEscapeState stringLiteralEscape_;
        states::ErrorState error_;
    };
}
