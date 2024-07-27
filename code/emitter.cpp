#include "emitter.hpp"

#include <fstream>
#include <stdexcept>
#include <filesystem>

Emitter::Emitter(const std::string& path) : path_(path) {}

void Emitter::Write() {
    std::ofstream file(path_);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file at path: " + path_);
    }

    file << header_;
    file << code_;
    file.close();
}

void Emitter::AddHeaderLine(const std::string& text) {
    header_ += text + '\n';
}

void Emitter::EmitLine(const std::string& text) {
    code_ += text + '\n';
}

void Emitter::Emit(const std::string& text) {
    code_ += text;
}