#include <cassert>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>
#include <optional>

#include "lexer.hpp"
#include "token.hpp"

Lexer::Lexer(const std::string& source) : sourceCode_(source + '\n') {
    NextChar();
}

Token Lexer::GetToken() {
    SkipWhitespace();
    SkipComment();

    auto token = CheckSpecialSymbolToken();
    if (token) {
        return *token;
    }

    token = CheckOperatorToken();
    if (token) {
        return *token;
    }

    token = CheckStringToken();
    if (token) {
        return *token;
    }

    token = CheckNumberToken();
    if (token) {
        return *token;
    }

    token = CheckIdentifierOrKeywordToken();
    if (token) {
        return *token;
    }

    Abort("Unkown token{" + std::string{curChar_} + "}. Position = " + std::to_string(curPos_));
    return Token("UNKNOWN", TokenType::UNKNOWN);
}

std::optional<Token> Lexer::CheckSpecialSymbolToken() {
    auto res = g_specialSymbolsMap.find(curChar_);
    if (res != g_specialSymbolsMap.end()) {
        NextChar();
        return Token(std::string{res->first}, res->second);
    }
    return {};
}

std::optional<Token> Lexer::CheckOperatorToken() {
    // Check two symbols operators
    auto res = g_operatorsMap.find(std::string{curChar_} + Peek());
    if (res != g_operatorsMap.end()) {
        NextChar();
        NextChar();
        return Token(res->first, res->second);
    }

    // Check one symbol operators
    res = g_operatorsMap.find(std::string{curChar_});
    if (res != g_operatorsMap.end()) {
        NextChar();
        return Token(res->first, res->second);
    }

    return {};
}

std::optional<Token> Lexer::CheckStringToken() {
    if (curChar_ != '"') {
        return {};
    }
    NextChar();
    auto startPos = curPos_;
    while (curChar_ != '"') {
        if (curChar_ == '\r' || curChar_ == '\n' || curChar_ == '\t' || curChar_ == '\\' || curChar_ == '%') {
            Abort("Illegal character in string. Position = " + std::to_string(curPos_));
            return {};
        }
        NextChar();
    }
    std::string text = sourceCode_.substr(startPos, curPos_ - startPos);
    NextChar();
    return Token(text, TokenType::STRING);
}

std::optional<Token> Lexer::CheckNumberToken() {
    if (!std::isdigit(curChar_)) {
        return {};
    }
    auto startPos = curPos_;
    auto nextChar = Peek();
    while (std::isdigit(Peek())) {
        NextChar();
    }

    if('.' == Peek()) {
        // Decimal
        NextChar();
        if (!std::isdigit(Peek())) {
            Abort("Illegal character in number. Position = " + std::to_string(curPos_ + 1));
            return {};
        }
        while (std::isdigit(Peek())) {
            NextChar();
        }
    }
    NextChar();
    std::string text = sourceCode_.substr(startPos, curPos_ - startPos);
    return Token(text, TokenType::NUMBER);
}

std::optional<Token> Lexer::CheckIdentifierOrKeywordToken() {
    if (!std::isalpha(curChar_)) {
        return {};
    }
    auto startPos = curPos_;
    while(std::isalnum(Peek())) {
        NextChar();
    }
    NextChar();
    auto text = sourceCode_.substr(startPos, curPos_ - startPos);

    auto res = g_keywordsMap.find(text);
    if (res != g_keywordsMap.end()) {
        return Token(res->first, res->second);
    }

    return Token(text, TokenType::IDENT);
}

char Lexer::NextChar() {
    curPos_++;
    if (IsEnd()) {
        curChar_ = '\0';
    } else {
        curChar_ = sourceCode_[curPos_];
    }
    return curChar_;
}

char Lexer::Peek() const {
    return (curPos_ + 1 >= sourceCode_.size()) ? '\0' : sourceCode_[curPos_ + 1];
}

char Lexer::GetCurChar() const {
    return curChar_;
}

bool Lexer::IsEnd() const {
    return curPos_ >= sourceCode_.size();
}

void Lexer::SkipWhitespace() {
    while (curChar_ == ' ' || curChar_ == '\t') {
        NextChar();
    }
}

void Lexer::SkipComment() {
    if (curChar_ == '#') {
        while (curChar_ != '\n') {
            NextChar();
        }
    }
}

void Lexer::Abort(const std::string &message) const {
    std::cerr << "Lexer::Abort: " << message << std::endl;
}
