#include <iostream>
#include <any>
#include "Token.h"
using namespace std;

Token::Token(TokenType type, string lexeme, any literal, int line) {
    this->type = type;
    this->lexeme = lexeme;
    this->literal = literal;
    this->line = line;
}

string Token::toString() {
    return (type + " " + lexeme + " " + any_cast<string>(literal));
}