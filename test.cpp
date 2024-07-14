#include "test.hpp"
#include "lexer.hpp"

#include <cstdio>
#include <iostream>
#include <string>

void TestLexer() {
    {
        const std::string code = 
            R"( + # new comment
                -
                ==
                # other comment

                -)";
        Lexer lexer(code);
        while (!lexer.IsEnd()) {
            auto token = lexer.GetToken();
            token.Print();
        }
        printf("\n");
    }
}