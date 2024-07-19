#include "token.hpp"
#include <cassert>
#include <functional>
#include <string>
#include <unordered_map>

const std::unordered_map<char, TokenType> g_specialSymbolsMap =
{
    {'\0',  TokenType::EOFT},
    {'\n',  TokenType::NEWLINE}
};

const std::unordered_map<std::string, TokenType> g_operatorsMap =
{
    {"+",  TokenType::PLUS},
    {"-",  TokenType::MINUS},
    {"*",  TokenType::ASTERISK},
    {"/",  TokenType::SLASH},
    {"=",  TokenType::EQ},
    {"==", TokenType::EQEQ},
    {"!=", TokenType::NOTEQ},
    {"<",  TokenType::LT},
    {"<=", TokenType::LTEQ},
    {">",  TokenType::GT},
    {">=", TokenType::GTEQ}
};

const std::unordered_map<std::string, TokenType> g_keywordsMap =
{
    {"LABEL",    TokenType::LABEL},
    {"GOTO",     TokenType::GOTO},
    {"PRINT",    TokenType::PRINT},
    {"INPUT",    TokenType::INPUT},
    {"LET",      TokenType::LET},
    {"IF",       TokenType::IF},
    {"THEN",     TokenType::THEN},
    {"ENDIF",    TokenType::ENDIF},
    {"WHILE",    TokenType::WHILE},
    {"REPEAT",   TokenType::REPEAT},
    {"ENDWHILE", TokenType::ENDWHILE}
};

const std::unordered_map<TokenType, std::string> g_tokenTypeNamesMap = 
{
        // Other
    {TokenType::UNKNOWN, "UNKNOWN"},
    {TokenType::EOFT, "EOFT"},
	{TokenType::NEWLINE, "NEWLINE"},
	{TokenType::NUMBER, "NUMBER"},
	{TokenType::IDENT, "IDENT"},
	{TokenType::STRING, "STRING"},

	// Keywords
	{TokenType::LABEL, "LABEL"},
	{TokenType::GOTO, "GOTO"},
	{TokenType::PRINT, "PRINT"},
	{TokenType::INPUT, "INPUT"},
	{TokenType::LET, "LET"},
	{TokenType::IF, "IF"},
	{TokenType::THEN, "THEN"},
	{TokenType::ENDIF, "ENDIF"},
	{TokenType::WHILE, "WHILE"},
	{TokenType::REPEAT, "REPEAT"},
	{TokenType::ENDWHILE, "ENDWHILE"},

	// Operators
	{TokenType::EQ, "EQ"},
	{TokenType::PLUS, "PLUS"},
	{TokenType::MINUS, "MINUS"},
	{TokenType::ASTERISK, "ASTERISK"},
	{TokenType::SLASH, "SLASH"},
	{TokenType::EQEQ, "EQEQ"},
	{TokenType::NOTEQ, "NOTEQ"},
	{TokenType::LT, "LT"},
	{TokenType::LTEQ, "LTEQ"},
	{TokenType::GT, "GT"},
	{TokenType::GTEQ, "GTEQ"}
};

Token::Token() : text_("DEFAULT"), type_(TokenType::UNKNOWN) {}

Token::Token(const std::string& text, TokenType type) : text_(text), type_(type) {}

size_t std::hash<TokenType>::operator()(TokenType type) const noexcept {
    return static_cast<size_t>(type);
}

void Token::Print() const {
    auto res = g_tokenTypeNamesMap.find(type_);
    if (g_tokenTypeNamesMap.end() == res) {
        assert("Can not find token name");
        return;
    }
    const std::string& name = res->second;
    if (TokenType::NEWLINE == type_) {
        printf("{\\n, %s}\n", name.c_str());
    } else if (TokenType::EOFT == type_) {
        printf("{\\0, %s}\n", name.c_str());
    } else {
        printf("{%s, %s}\n", text_.c_str(), name.c_str());
    }
}

std::string Token::GetText() const {
    if (TokenType::NEWLINE == type_) {
        return "\\n";
    } else if (TokenType::EOFT == type_) {
        return "\\0";
    } else {
        return text_;
    }
}

TokenType Token::GetType() const {
    return type_;
}