#pragma once

#include <iostream>
#include <string>
#include <list>
#include <variant>
#include <map>
#include "TokenType.h"
#include "Token.h"
using namespace std;

class Scanner {
    int start = 0;
    int current = 0;
    int line = 1;
    public:
    string source;
    list<Token> tokens; 
    // List<Token> tokens = new List<>(); original as directed : (a lo mejor nosotros no tenemos inicializar esto)
    inline static map<string, TokenType> keywords = {
        {"and", AND},
        {"class", CLASS},
        {"else", ELSE},
        {"false", FALSE},
        {"for", FOR},
        {"fun", FUN},
        {"if", IF},
        {"nil", NIL},
        {"or", OR},
        {"print", PRINT},
        {"return", RETURN},
        {"super", SUPER},
        {"this", THIS},
        {"true", TRUE},
        {"var", VAR},
        {"while", WHILE}
    };
    


    Scanner(string source);
    list<Token> scanTokens();
    bool isAtEnd();
    void scanToken(); 
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, variant<monostate, string, double, bool> literal);
    bool match(char expected);
    char peek();
    char peekNext();
    void String(); 
    bool isDigit(char c);
    void number();
    void identifier();
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
    int getSourceLength();
};