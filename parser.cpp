#include "parser.hpp"

#include <iostream>

Parser::Parser(Lexer& lexer) : lexer_(lexer) {
    NextToken();
    NextToken();
}

// program ::= { statement }
void Parser::Program() {
    SkipNewLines();
    while (!CheckCurToken(TokenType::EOFT)) {
        Statement();
    }
}

// statement ::= 
//     "PRINT" (expression | string) nl
//     | "IF" comparison "THEN" nl {statement} "ENDIF" nl
//     | "WHILE" comparison "REPEAT" nl {statement} "ENDWHILE" nl
//     | "LABEL" ident nl
//     | "GOTO" ident nl
//     | "LET" ident "=" expression nl
//     | "INPUT" ident nl
void Parser::Statement() {
    if (CheckCurToken(TokenType::PRINT)) {
        PrintStatement();
    } else if (CheckCurToken(TokenType::IF)) {
        IfStatement();
    } else if (CheckCurToken(TokenType::WHILE)) {
        WhileStatement();
    } else if (CheckCurToken(TokenType::LABEL)) {
        LabelStatement();
    } else if (CheckCurToken(TokenType::GOTO)) {
        GoToStatement();
    } else if (CheckCurToken(TokenType::LET)) {
        LetStatement();
    } else if (CheckCurToken(TokenType::INPUT)) {
        InputStatement();
    } else {
        UnexpectedTokenAbort();
    }
    NewLine();
}

void Parser::PrintStatement() {
    std::cout << "Parser::PrintStatement()\n";
    NextToken();
    if (CheckCurToken(TokenType::STRING)) {
        NextToken();
    } else {
        Expression();
    }
}

void Parser::IfStatement() {
    std::cout << "Parser::IfStatement()\n";
    NextToken();
    Comparsion();
    Match(TokenType::THEN);
    NewLine();

    while(!CheckCurToken(TokenType::ENDIF)) {
        Statement();
    }

    // Match(TokenType::ENDIF);  We already checked ENDIF in the while-loop, so maybe just NextToken() ?
    NextToken();
}

void Parser::WhileStatement() {
    std::cout << "Parser::WhileStatement()\n";
    NextToken();
    Comparsion();
    Match(TokenType::REPEAT);
    NewLine();

    while(!CheckCurToken(TokenType::ENDWHILE)) {
        Statement();
    }

    NextToken();
}

void Parser::LabelStatement() {
    std::cout << "Parser::LabelStatement()\n";
    NextToken();
    Match(TokenType::IDENT);
}

void Parser::GoToStatement() {
    std::cout << "Parser::GoToStatement()\n";
    NextToken();
    Match(TokenType::IDENT);
}

void Parser::LetStatement() {
    std::cout << "Parser::LetStatement()\n";
    NextToken();
    Match(TokenType::IDENT);
    Match(TokenType::EQ);
    Expression();
}

void Parser::InputStatement() {
    std::cout << "Parser::InputStatement()\n";
    NextToken();
    Match(TokenType::IDENT);
}


void Parser::Expression() {
    NextToken();
}

void Parser::Comparsion() {
    NextToken();
    NextToken();
    NextToken();
}

void Parser::NewLine() {
    Match(TokenType::NEWLINE);
    SkipNewLines();
}

bool Parser::CheckCurToken(TokenType type) const {
    return type == curToken_.GetType();
}

bool Parser::CheckPeekToken(TokenType type) const {
    return type == peekToken_.GetType();
}

void Parser::Match(TokenType type) {
    if (!CheckCurToken(type)) {
        UnexpectedTokenAbort(type);
    }
    NextToken();
}

void Parser::NextToken() {
    curToken_ = peekToken_;
    peekToken_ = lexer_.GetToken();
}

void Parser::Abort(const std::string& message) const {
    std::cerr << "Parser::Abort: " << message << std::endl;
    assert(false);
}

void Parser::UnexpectedTokenAbort(std::optional<TokenType> type) const {
    std::string tokenTypeName;
    const auto& resCur = g_tokenTypeNamesMap.find(curToken_.GetType());
    if (resCur != g_tokenTypeNamesMap.end()) {
        tokenTypeName = resCur->second;
    }

    std::string expectedTypeName{"Undefined"};
    if (type) {
        const auto& resExpected = g_tokenTypeNamesMap.find(type.value());
        if (resExpected != g_tokenTypeNamesMap.end()) {
            expectedTypeName = resExpected->second;
        }
    }
    std::string message = "Parser::UnexpectedTokenAbort! Token {" + curToken_.GetText() + " : " +
        tokenTypeName + "} doesn't match with { ... : " + expectedTypeName + "}";
    Abort(message);
}

void Parser::SkipNewLines() {
    while (CheckCurToken(TokenType::NEWLINE)) {
        NextToken();
    }
}