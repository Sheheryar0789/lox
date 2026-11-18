#pragma once
#include <iostream>
#include <string>
#include <any>
#include "TokenType.h"
using namespace std;

class Token {
    public:
    TokenType type;
    string lexeme;
    any literal; // was Object datatype in java
    int line; 
    
    Token(TokenType type, string lexeme, any literal, int line);

    string toString();
};