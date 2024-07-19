#include "parser.hpp"

#include <iostream>

Parser::Parser(Lexer& lexer) : lexer_(lexer) {
    NextToken();
    NextToken();
}

// program ::= { statement }
void Parser::Program() {
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
    }
    NewLine();
}

void Parser::PrintStatement() {
    std::cout << "Parser::PrintStatement()";
    curToken_.Print();
    NextToken();
    curToken_.Print();
    if (CheckCurToken(TokenType::STRING)) {
        NextToken();
    } else {
        Expression();
    }
}


void Parser::Expression() {

}

void Parser::NewLine() {
    Match(TokenType::NEWLINE);
    while (CheckCurToken(TokenType::NEWLINE)) {
        NextToken();
    }
}

bool Parser::CheckCurToken(TokenType type) const {
    return type == curToken_.GetType();
}

bool Parser::CheckPeekToken(TokenType type) const {
    return type == peekToken_.GetType();
}

void Parser::Match(TokenType type) {
    if (!CheckCurToken(type)) {
        std::string tokenTypeName;
        std::string expectedTypeName;

        const auto& resCur = g_tokenTypeNamesMap.find(curToken_.GetType());
        const auto& resExpected = g_tokenTypeNamesMap.find(type);
        if (resCur != g_tokenTypeNamesMap.end()  && resExpected != g_tokenTypeNamesMap.end()) {
            tokenTypeName = resCur->second;
            expectedTypeName = resExpected->second;
        }
        std::string message = "Error! Token {" + curToken_.GetText() + ":" +
            tokenTypeName + "} doesn't match with " + expectedTypeName;
        Abort(message);
    }
    NextToken();
}

void Parser::NextToken() {
    curToken_ = peekToken_;
    peekToken_ = lexer_.GetToken();
}

void Parser::Abort(const std::string& message) const {
    std::cerr << "Parser::Abort: " << message << std::endl;
}