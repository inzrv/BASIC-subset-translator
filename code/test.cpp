#include "test.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "token.hpp"
#include "emitter.hpp"

#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>

void TestLexer() {
    {   
        Lexer lexer("../input/prog.tt");
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
        // Lexer lexer{"../input/prog.tt"};
        // Parser parser{lexer};
        // parser.Program();
    }
}

void TestEmitter() {
    {
        Lexer lexer{"../input/prog.tt"};
        Emitter emitter("../output/prog.c");
        Parser parser{lexer, emitter};
        parser.Program();
        emitter.Write();
    }
}