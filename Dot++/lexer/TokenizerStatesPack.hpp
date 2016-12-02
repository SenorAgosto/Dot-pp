#pragma once

#include <Dot++/lexer/states/InitialState.hpp>
#include <Dot++/lexer/states/BeginSlashLineCommentState.hpp>
#include <Dot++/lexer/states/EndMultiLineCommentState.hpp>
#include <Dot++/lexer/states/ErrorState.hpp>
#include <Dot++/lexer/states/HashLineCommentState.hpp>
#include <Dot++/lexer/states/InitialState.hpp>
#include <Dot++/lexer/states/MultiLineCommentState.hpp>
#include <Dot++/lexer/states/MultiLineEscapeState.hpp>
#include <Dot++/lexer/states/SlashLineCommentState.hpp>
#include <Dot++/lexer/states/StringLiteralEscapeState.hpp>
#include <Dot++/lexer/states/StringLiteralState.hpp>

namespace dot_pp { namespace lexer {
    enum class TokenizerState;
    class TokenizerStateInterface;
}}

namespace dot_pp { namespace lexer {
    
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
}}
