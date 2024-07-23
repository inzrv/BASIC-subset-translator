#pragma once

#include <string>

class Emitter {
public:
    explicit Emitter(const std::string& path);
    void Write();
    void AddHeaderLine(const std::string& text);
    void EmitLine(const std::string& text);
    void Emit(const std::string& text);
private:
    std::string code_;
    std::string header_;
    std::string path_;
};