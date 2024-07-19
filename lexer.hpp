#pragma once

#include <string>
#include <unordered_map>

#include "token.hpp"

class Lexer {
public:
    explicit Lexer(const std::string& fileName);
    void Abort(const std::string& message) const ;
    char GetCurChar() const;
    bool IsEnd() const;
    void SkipWhitespace();
    void SkipComment();
    Token GetToken();
    char NextChar();
private:
    char Peek() const;
    std::optional<Token> CheckSpecialSymbolToken();
    std::optional<Token> CheckOperatorToken();
    std::optional<Token> CheckStringToken();
    std::optional<Token> CheckNumberToken();
    std::optional<Token> CheckIdentifierOrKeywordToken();

    std::string sourceCode_;
    char curChar_ = '\0';
    int curPos_ = -1;
};
