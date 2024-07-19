#include "test.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "token.hpp"

#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>

void TestLexer() {
    {   
        Lexer lexer("../test_code/prog.tt");
        while (!lexer.IsEnd()) {
            auto token = lexer.GetToken();
            token.Print();
            if (TokenType::UNKNOWN == token.GetType()) {
                break;
            }
        }
        printf("\n");
    }
}

void TestParser() {
    {
        Lexer lexer{"../test_code/prog.tt"};
        Parser parser{lexer};
        parser.Program();
    }
}