#pragma once

#include "lexer.hpp"

class Parser {
public:
    explicit Parser(Lexer& lexer);
    void Program();
    void Statement();
    void PrintStatement();
    void Expression();
    void NewLine();
    bool CheckCurToken(TokenType type) const;
    bool CheckPeekToken(TokenType type) const;
    void Match(TokenType type);
    void NextToken();
    void Abort(const std::string& message) const;
private:
    Lexer& lexer_;
    Token curToken_;
    Token peekToken_;
};