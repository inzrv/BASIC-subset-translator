#include "parser.hpp"

#include <iostream>

Parser::Parser(Lexer& lexer, Emitter& emitter) : lexer_(lexer), emitter_(emitter) {
    NextToken();
    NextToken();
}

// program ::= { statement }
void Parser::Program() {
    emitter_.AddHeaderLine("#include <stdio.h>");
    emitter_.AddHeaderLine("int main(void) {");

    SkipNewLines();
    while (!CheckCurToken(TokenType::EOFT)) {
        Statement();
    }

    if (!CheckAllLabelsAreDeclared()) {
        // TODO: Print this undeclared label
        Abort("Attempting to GOTO to undeclared label!");
    }

    emitter_.EmitLine("return 0;");
    emitter_.EmitLine("}");
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
        emitter_.EmitLine("printf(\"" + curToken_.GetText() + "\\n\");");
        NextToken();
    } else {
        emitter_.Emit("printf(\"%.2f\\n\", (float)(");
        Expression();
        emitter_.EmitLine("));");
    }
}

void Parser::IfStatement() {
    NextToken();
    emitter_.Emit("if (");
    Comparsion();
    Match(TokenType::THEN);
    NewLine();
    emitter_.EmitLine(") {");

    while(!CheckCurToken(TokenType::ENDIF)) {
        Statement();
    }

    // Match(TokenType::ENDIF);  We already checked ENDIF in the while-loop, so maybe just NextToken() ?
    NextToken();
    emitter_.EmitLine("}");
}

void Parser::WhileStatement() {
    std::cout << "Parser::WhileStatement()\n";
    NextToken();
    emitter_.Emit("while (");
    Comparsion();
    Match(TokenType::REPEAT);
    NewLine();
    emitter_.EmitLine(") {");

    while(!CheckCurToken(TokenType::ENDWHILE)) {
        Statement();
    }

    NextToken();
    emitter_.EmitLine("}");
}

void Parser::LabelStatement() {
    std::cout << "Parser::LabelStatement()\n";
    NextToken();
    if (labelsDeclared_.find(curToken_) != labelsDeclared_.end()) {
        Abort("Label already exists: " + curToken_.GetText());
    }
    labelsDeclared_.insert(curToken_);
    emitter_.EmitLine(curToken_.GetText() + ":");
    Match(TokenType::IDENT);
}

void Parser::GoToStatement() {
    std::cout << "Parser::GoToStatement()\n";
    NextToken();
    labelsGoTo_.insert(curToken_);
    emitter_.EmitLine("goto " + curToken_.GetText() + ";");
    Match(TokenType::IDENT);
}

void Parser::LetStatement() {
    std::cout << "Parser::LetStatement()\n";
    NextToken();

    if (symbols_.find(curToken_) == symbols_.end()) {
        emitter_.AddHeaderLine("float " + curToken_.GetText() + ";");
        symbols_.insert(curToken_);
    }

    emitter_.Emit(curToken_.GetText() + " = ");
    Match(TokenType::IDENT);
    Match(TokenType::EQ);
    Expression();
    emitter_.EmitLine(";");
}

void Parser::InputStatement() {
    std::cout << "Parser::InputStatement()\n";
    NextToken();

    if (symbols_.find(curToken_) == symbols_.end()) {
        emitter_.AddHeaderLine("float " + curToken_.GetText() + ";");
        symbols_.insert(curToken_);
    }

    emitter_.EmitLine("scanf(\"%f\", &" + curToken_.GetText() + ");");
    Match(TokenType::IDENT);
}

void Parser::Comparsion() {
    std::cout << "Parser::Comparsion()\n";
    Expression(); // skip all tokens from expression
    emitter_.Emit(curToken_.GetText());
    if (!IsComparsionOperator()) {
        UnexpectedTokenAbort();
    } else {
        NextToken();
        Expression();
    }
}

// expression ::= term {( "-" | "+" ) term}
void Parser::Expression() {
    std::cout << "Parser::Expression()\n";
    Term();
    // Why do we expect more than 1 sign?
    // TODO: Check later
    while(IsSign()) {
        emitter_.Emit(curToken_.GetText());
        NextToken();
        Term();
    }
}

// term ::= unary {( "/" | "*" ) unary}
void Parser::Term() {
    std::cout << "Parser::Term()\n";
    Unary();
    // Why do we expect more than 1 operator?
    // TODO: Check later
    while(IsMultOrDiv()) {
        emitter_.Emit(curToken_.GetText());
        NextToken();
        Unary();
    }
}

// unary ::= ["+" | "-"] primary
void Parser::Unary() {
    std::cout << "Parser::Unary()\n";
    if (IsSign()) {
        emitter_.Emit(curToken_.GetText());
        NextToken();
    }
    Primary();
}

// primary ::= number | ident
void Parser::Primary() {
    std::cout << "Parser::Primary():" << curToken_.GetText() << std::endl;
    if (CheckCurToken(TokenType::IDENT)) {
        emitter_.Emit(curToken_.GetText());
        // TODO: Replace with contains() ?
        if (symbols_.find(curToken_) == symbols_.end()) {
            Abort("Referencing variable before assignment: " + curToken_.GetText());
        }
        NextToken();
    } else if (CheckCurToken(TokenType::NUMBER)) {
        emitter_.Emit(curToken_.GetText());
        NextToken();
    } else {
        UnexpectedTokenAbort();
    }
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

bool Parser::CheckAllLabelsAreDeclared() const {
    for (const auto& label : labelsGoTo_) {
        if (labelsDeclared_.find(label) == labelsDeclared_.end()) {
            return false;
        }
    }
    return true;
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

bool Parser::IsComparsionOperator() {
    auto type = curToken_.GetType();
    return (
        type == TokenType::EQEQ ||
        type == TokenType::NOTEQ ||
        type == TokenType::LT ||
        type == TokenType::LTEQ ||
        type == TokenType::GT ||
        type == TokenType:: GTEQ);
}

bool Parser::IsSign() {
    auto type = curToken_.GetType();
    return (type == TokenType::PLUS || type == TokenType::MINUS);
}

bool Parser::IsMultOrDiv() {
    auto type = curToken_.GetType();
    return (type == TokenType::ASTERISK || type == TokenType::SLASH);
}