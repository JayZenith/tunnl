#include <gtest/gtest.h>

#include "../include/tunnl/Scanner.h"

// using namespace Lox;

// namespace
// {
bool checkLiteralsEqual(TokenType type, const std::any& el, const std::any& l)
{
    if (el.type() != l.type()) {
        return false;
    }

    switch (type) {
    case TokenType::STRING:
        return std::any_cast<const std::string&>(el) == std::any_cast<const std::string&>(l);
    case TokenType::NUMBER:
        return std::any_cast<double>(el) == std::any_cast<double>(l);
    default:
        return true;
    }
}

void checkTokensEqual(const std::vector<Token>& ets, const std::vector<Token>& ts)
{
    ASSERT_EQ(ets.size(), ts.size());
    for (std::size_t i = 0; i < ts.size(); ++i) {
        EXPECT_EQ(ets[i].getType(), ts[i].getType()) << "Token types differ at index " << i;
        EXPECT_EQ(ets[i].getText(), ts[i].getText()) << "Token lexemes differ at index " << i;
        EXPECT_EQ(ets[i].getLine(), ts[i].getLine()) << "Token lines differ at index " << i;
        EXPECT_TRUE(::checkLiteralsEqual(ets[i].getType(), ets[i].getLiteral(), ts[i].getLiteral()))
            << "Literals differ at index " << i;
    }
}
// } // end of anonymous namespace

TEST(ScannerTests, Basic)
{
    const auto testScript = R"(print "Hello, world" 42)";
    Scanner scanner{testScript};
    const auto tokens = scanner.scanTokens();
    /* clang-format off */
    std::vector<Token> expectedTokens = {
        Token{TokenType::PRINT, "print", 1},
        Token{TokenType::STRING, "\"Hello, world\"", std::string{"Hello, world"}, 1},
        Token{TokenType::NUMBER, "42", 42., 1},
        Token{TokenType::TokenEOF, "", 1},
    };
    /* clang-format on */

    ::checkTokensEqual(expectedTokens, tokens);
}

TEST(ScannerTests, Comment)
{
    const auto testScript = R"(// this is a comment
print "Hello, world" // another comment)";

    Scanner scanner{testScript};
    const auto tokens = scanner.scanTokens();
    /* clang-format off */
    std::vector<Token> expectedTokens = {
        Token{TokenType::PRINT, "print", 2},
        Token{TokenType::STRING, "\"Hello, world\"", std::string{"Hello, world"}, 2},
        Token{TokenType::TokenEOF, "", 2},
    };
    /* clang-format on */

    ::checkTokensEqual(expectedTokens, tokens);
}

TEST(ScannerTests, Expression)
{
    const auto testScript = R"(var x = 2 + 2)";

    Scanner scanner{testScript};
    const auto tokens = scanner.scanTokens();
    /* clang-format off */
    std::vector<Token> expectedTokens = {
        Token{TokenType::VAR, "var", 1},
        Token{TokenType::IDENTIFIER, "x", 1},
        Token{TokenType::EQUAL, "=", 1},
        Token{TokenType::NUMBER, "2", 2., 1},
        Token{TokenType::PLUS, "+", 1},
        Token{TokenType::NUMBER, "2", 2., 1},
        Token{TokenType::TokenEOF, "", 1},
    };
    /* clang-format on */

    ::checkTokensEqual(expectedTokens, tokens);
}