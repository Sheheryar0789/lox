#pragma once
#include <iostream>
#include <string>
#include <variant>
#include "TokenType.h"
using namespace std;

class Token {
    public:
    TokenType type;
    string lexeme;
    variant<monostate, string, double, bool> literal; // was Object datatype in java
    int line; 
    
    Token(TokenType type, string lexeme, variant<monostate, string, double, bool> literal, int line);

    string toString();
    string literalToString(variant<monostate, string, double, bool> &literal);
    string tokenToString(TokenType type);
};