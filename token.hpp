#pragma once

#include <unordered_map>
#include <string>

enum class TokenType {
    // Other
    UNKNOWN = -2,
    EOFT = -1,
	NEWLINE= 0,
	NUMBER = 1,
	IDENT = 2,
	STRING = 3,

	// Keywords
	LABEL = 101,
	GOTO = 102,
	PRINT = 103,
	INPUT = 104,
	LET = 105,
	IF = 106,
	THEN = 107,
	ENDIF = 108,
	WHILE = 109,
	REPEAT = 110,
	ENDWHILE = 111,

	// Operators
	EQ = 201, 
	PLUS = 202,
	MINUS = 203,
	ASTERISK = 204,
	SLASH = 205,
	EQEQ = 206,
	NOTEQ = 207,
	LT = 208,
	LTEQ = 209,
	GT = 210,
	GTEQ = 211
};

struct Token {
    Token() = default;
    Token(const std::string& text, TokenType type);
    Token(const Token& other) = default;
    void Print() const;
    std::string text_;
    TokenType type_;
};

namespace std {
    template <>
    struct hash<TokenType> {
        std::size_t operator()(TokenType type) const noexcept;
    };
}

extern const std::unordered_map<char, TokenType> g_specialSymbolsMap;
extern const std::unordered_map<std::string, TokenType> g_operatorsMap;
extern const std::unordered_map<std::string, TokenType> g_keywordsMap;
extern const std::unordered_map<TokenType, std::string> g_tokenTypeNamesMap;