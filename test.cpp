#include "test.hpp"
#include "lexer.hpp"
#include "token.hpp"

#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>

void TestLexer() {
    {        
        const std::string code = 
            R"(LET foo = bar
            # comment
            IF 1.123 == 2 THEN "true")";
        Lexer lexer(code);
        while (!lexer.IsEnd()) {
            auto token = lexer.GetToken();
            token.Print();
            if (TokenType::UNKNOWN == token.type_) {
                break;
            }
        }
        printf("\n");
    }
}