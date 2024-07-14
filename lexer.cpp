#include "lexer.hpp"
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <optional>

std::unordered_map<std::string, TokenType> textToTokenType_g =
{
    // Other
    {"\0", TokenType::EOFT},
    {"\n", TokenType::NEWLINE},

    // Keywords
    {"LET", TokenType::LET},

    // Operators
    {"+",  TokenType::PLUS},
    {"-",  TokenType::MINUS},
    {"*",  TokenType::ASTERISK},
    {"/",  TokenType::SLASH},
    {"=",  TokenType::EQ},
    {"==", TokenType::EQEQ},
    {"!=", TokenType::NOTEQ},
    {"<",  TokenType::LT},
    {"<=", TokenType::LTEQ},
    {">",  TokenType::GT},
    {">=", TokenType::GTEQ}
};

static std::optional<Token> CheckToken(const std::string& text) {
    auto res = textToTokenType_g.find(text);
    if (res == textToTokenType_g.end()) {
        return {};
    }
    return Token(res->first, res->second);
}


Lexer::Lexer(const std::string& source) : sourceCode_(source + '\n') {
    NextChar();
}

Token Lexer::GetToken() {
    // TODO: Fix that
    if (curChar_ == '\0') {
        return Token("\0", TokenType::EOFT);
    }

    SkipWhitespace();
    SkipComment();

    Token token;

    // Check one symbol tokens
    std::string prefixOne;
    prefixOne += curChar_;
    auto tokenOne = CheckToken(prefixOne);
    NextChar();

    // Check two symbols tokens
    std::string prefixTwo = prefixOne + curChar_;
    auto tokenTwo = CheckToken(prefixTwo);
    if (tokenTwo) {
        NextChar();
        return *tokenTwo;
    }

    // If there is no token with prefixTwo check only first symbol 
    if (tokenOne) {
        return *tokenOne;
    }

    // Check if string token
    


    Abort("Unkown token{" + prefixOne + "}");
    return Token("UNKNOWN", TokenType::UNKNOWN);
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
    return (curChar_ + 1 >= sourceCode_.size()) ? '\0' : sourceCode_[curPos_ + 1];
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

Token::Token(const std::string& text, TokenType type) :text_(text), type_(type) {}

void Token::Print() const {
    if (TokenType::NEWLINE == type_) {
        printf("{\\n}");
    } else {
        printf("{%s}", text_.c_str());
    }
}