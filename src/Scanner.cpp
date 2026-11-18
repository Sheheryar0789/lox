#include <iostream>
#include <string>
#include "Scanner.h"
#include "Lox.h"
using namespace std;

Scanner::Scanner(string source) {
    this->source = source;

    keywords.insert({"and", AND});
    keywords.insert({"class", CLASS});
    keywords.insert({"else", ELSE});
    keywords.insert({"false", FALSE});
    keywords.insert({"for", FOR});
    keywords.insert({"fun", FUN});
    keywords.insert({"if", IF});
    keywords.insert({"nil", NIL});
    keywords.insert({"or", OR});
    keywords.insert({"print", PRINT});
    keywords.insert({"return", RETURN});
    keywords.insert({"super", SUPER});
    keywords.insert({"this", THIS});
    keywords.insert({"true", TRUE});
    keywords.insert({"var", VAR});
    keywords.insert({"while", WHILE});
}

list<Token> Scanner::scanTokens() {
    while (!isAtEnd()){
        // we are at the beginning of the next lexeme.
        start = current;
        scanToken();
    }
    Token newToken(END_OF_FILE, "", NULL, line);
    tokens.add(newToken); //Token add() isn't implemented yet
    return tokens;
}

bool Scanner::isAtEnd(){
    return current >= source.size();
}

void Scanner::scanToken() {
    char c = advance();
    switch (c)
    {
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
    // we'll handle default case later
    }
}

char Scanner::advance() {
    return source.at(current++);
}

void Scanner::addToken(TokenType type){
    addToken(type, NULL);
}

void Scanner::addToken(TokenType type, any literal){
    string text = source.substr(start, current);
    tokens.add(new Token(type, text, literal, line)); //Token add() isn't implemented yet
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
    string value = source.substr(start+1, current-1);
    addToken(STRING, value);
}

bool Scanner::isDigit(char c) {
    return c>= '0' && c <= '9';
}

void Scanner::number() {
    while (isDigit(peek())) advance();

    if (peek() == '.' && isDigit(peekNext())){
        advance();
        while(isDigit(peek())) advance();
    }
    addToken(NUMBER, stod(source.substr(start, current)));
}

char Scanner::peekNext() {
    if (current + 1 >= source.size()) return '\0';
    return source.at(current+1);
}

void Scanner::identifier() {
    while (isAlphaNumeric(peek())) advance();
    string text = source.substr(start, current);
    try {
        TokenType type = keywords.at(text);
        addToken(type);
    } catch ( const out_of_range& e) {
        addToken(IDENTIFIER);
    } 
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

