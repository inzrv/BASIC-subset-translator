#pragma once

#include "lexer.hpp"
#include "emitter.hpp"

#include <unordered_set>

class Parser {
public:
    Parser(Lexer& lexer, Emitter& emitter);
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
    void Term();
    void Unary();
    void Primary();
    void Comparsion();
    void NewLine();
    bool CheckCurToken(TokenType type) const;
    bool CheckPeekToken(TokenType type) const;
    void Match(TokenType type);
    void NextToken();
    void Abort(const std::string& message) const;
private:
    void SkipNewLines();
    bool IsComparsionOperator();
    bool IsSign();
    bool IsMultOrDiv();
    void UnexpectedTokenAbort(std::optional<TokenType> type = std::nullopt) const;
    bool CheckAllLabelsAreDeclared() const;

    Lexer& lexer_;
    Emitter& emitter_;

    Token curToken_;
    Token peekToken_;
    std::unordered_set<Token> labelsDeclared_;
    std::unordered_set<Token> labelsGoTo_;
    std::unordered_set<Token> symbols_;
};