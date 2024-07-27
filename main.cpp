#include <fstream>
#include <iostream>
#include <filesystem>

#include "test.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "emitter.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file>\n";
        return 1;
    }

    std::string sourceFileName = argv[1];
    const std::filesystem::path sourcePath{sourceFileName};
    std::filesystem::path destinationPath{sourcePath};
    destinationPath.replace_extension(".c");

    try {
        Lexer lexer{sourcePath.string()};
        Emitter emitter(destinationPath.string());
        Parser parser{lexer, emitter};
        parser.Program();
        emitter.Write();
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
}