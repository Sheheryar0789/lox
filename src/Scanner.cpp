#include <iostream>
#include <string>
#include "Scanner.h"
#include "Lox.h"
using namespace std;

Scanner::Scanner(string source) {
    this->source = source;
}

list<Token> Scanner::scanTokens() {
    while (!isAtEnd()){
        // we are at the beginning of the next lexeme.
        start = current;
        
        scanToken();
    }
    variant<monostate, string, double, bool> nullLiteral;
    Token newToken(END_OF_FILE, "", nullLiteral, line);
    tokens.push_back(newToken);
    return tokens;
}

bool Scanner::isAtEnd(){
    return current >= this->getSourceLength();
}

void Scanner::scanToken() {
    char c = advance();
    switch (c)
    {
    //singe character tokens
    case '(': addToken(LEFT_PAREN); break;
    case ')': addToken(RIGHT_PAREN); break;
    case '{': addToken(LEFT_BRACE); break;
    case '}': addToken(RIGHT_BRACE); break;
    case ',': addToken(COMMA); break;
    case '.': addToken(DOT); break;
    case '-': addToken(MINUS); break;
    case '+': addToken(PLUS); break;
    case ';': addToken(SEMICOLON); break;
    case '*': addToken(STAR); break;
    //a bit of double ones
    case '!': addToken(match('=') ? BANG_EQUAL : BANG); break;
    case '=': addToken(match('=') ? EQUAL_EQUAL : EQUAL); break;
    case '<': addToken(match('=') ? LESS_EQUAL : LESS); break;
    case '>': addToken(match('=') ? GREATER_EQUAL : GREATER); break;
    // divide or comment?
    case '/': 
        if (match('/')) {
            //until the end of line
            while (peek() != '\n' && !isAtEnd()) advance();
        }else {
            addToken(SLASH);
        }
        break;
    //these too are ignored
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n': line++; break;
    //now string literals
    case '"': String(); break;
    
    default:
        if (isDigit(c)) {
            number();
        } else if (isAlpha(c)) {
            identifier();
        }        
        else {
            lox.error(line, "Unexpected character.");
        }
        break;
    }
}

char Scanner::advance() {
    return source.at(current++);
}

void Scanner::addToken(TokenType type){
    variant<monostate, string, double, bool> temp; //equivalent to null
    addToken(type, temp);
}

void Scanner::addToken(TokenType type, variant<monostate, string, double, bool> literal){
    string text = source.substr(start, current - start);
    Token newToken(type, text, literal, line);
    tokens.push_back(newToken); //Token add() isn't implemented yet
}

bool Scanner::match(char expected){
    if(isAtEnd()) return false;
    if (source.at(current) != expected) return false;

    current++;
    return true;
}

char Scanner::peek() {
    if(isAtEnd()) return '\0';
    return source.at(current);
}

void Scanner::String() {
    while (peek() != '"' && !isAtEnd()){
        if (peek() == '\n') line++;
        advance();
    }
    if(isAtEnd()){
        lox.error(line, "Unterminated string.");
        return;
    }

    advance();
    // string value = source.substr(start + 1, current - 1);
    string value = source.substr(start + 1, current - start - 2);
    
    addToken(STRING, value);
}


void Scanner::number() {
    while (isDigit(peek())) advance();
    
    if (peek() == '.' && isDigit(peekNext())){
        advance();
        while(isDigit(peek())) advance();
    }
    variant<monostate, string, double, bool> temp = stod(source.substr(start, current)); //stores the double variant of literal
    addToken(NUMBER, temp);
}

char Scanner::peekNext() {
    if (current + 1 >= this->getSourceLength()) return '\0';
    return source.at(current+1);
}

void Scanner::identifier() {
    while (isAlphaNumeric(peek())) advance();
    string text = source.substr(start, current - start);
    try {
        TokenType type = keywords.at(text);
        addToken(type);
    } catch (const out_of_range& e) {
        addToken(IDENTIFIER);
    } 
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

int Scanner::getSourceLength(){
    return static_cast<int>(source.length());
}