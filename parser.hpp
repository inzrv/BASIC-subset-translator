#pragma once

#include "lexer.hpp"

class Parser {
public:
    explicit Parser(Lexer& lexer);
    void Program();
    void Statement();
    void PrintStatement();
    void IfStatement();
    void WhileStatement();
    void LabelStatement();
    void GoToStatement();
    void LetStatement();
    void InputStatement();
    void Expression();
    void Comparsion();
    void NewLine();
    bool CheckCurToken(TokenType type) const;
    bool CheckPeekToken(TokenType type) const;
    void Match(TokenType type);
    void NextToken();
    void Abort(const std::string& message) const;
private:
    void SkipNewLines();
    void UnexpectedTokenAbort(std::optional<TokenType> type = std::nullopt) const;

    Lexer& lexer_;
    Token curToken_;
    Token peekToken_;
};