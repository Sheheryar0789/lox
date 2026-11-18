#pragma once

#include <iostream>
#include <string>
#include <list>
#include <any>
#include <map>
#include "TokenType.h"
#include "Token.h"
using namespace std;

class Scanner {
    public:
    string source;
    int start = 0;
    int current = 0;
    int line = 1;
    list<Token> tokens; 
    // List<Token> tokens = new List<>(); original as directed : (a lo mejor nosotros no tenemos inicializar esto)
    static map<string, TokenType> keywords;
    


    Scanner(string source);
    list<Token> scanTokens();
    bool isAtEnd();
    void scanToken(); 
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, any literal);
    bool match(char expected);
    char peek();
    char peekNext();
    void String(); 
    bool isDigit(char c);
    void number();
    void identifier();
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
};