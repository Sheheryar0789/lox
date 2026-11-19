#include <iostream>
#include <variant>
#include "Token.h"
using namespace std;

Token::Token(TokenType type, string lexeme, variant<monostate, string, double, bool> literal, int line) {
    this->type = type;
    this->lexeme = lexeme;
    this->literal = literal;
    this->line = line;
}

string Token::toString() {
    return (tokenToString(type) + " " + lexeme + " " + literalToString(literal));
}

string Token::literalToString(variant<monostate, string, double, bool> &literal) {
    if (holds_alternative<monostate>(literal)){
        return "null";
    } 
    else if (holds_alternative<string>(literal)) {
        return get<string>(literal);
    } else if (holds_alternative<double>(literal)){
        double temp = get<double>(literal);
        return to_string(temp);
    }
    else if (holds_alternative<bool>(literal)) {
        bool temp = get<bool>(literal);
        if (temp) {
            return "true";
        }
        return "false";
    } 
}

string Token::tokenToString(TokenType type) {
    switch (type)
    {
    case LEFT_PAREN: return "LEFT_PAREN"; break;
    case RIGHT_PAREN: return "RIGHT_PAREN"; break;
    case LEFT_BRACE: return "LEFT_BRACE"; break;
    case RIGHT_BRACE: return "RIGHT_BRACE"; break;
    case COMMA: return "COMMA"; break;
    case DOT: return "DOT"; break;
    case MINUS: return "MINUS"; break;
    case PLUS: return "PLUS"; break;
    case SEMICOLON: return "SEMICOLON"; break;
    case SLASH: return "SLASH"; break;
    case STAR: return "STAR"; break;
    case BANG: return "BANG"; break;
    case BANG_EQUAL: return "BANG_EQUAL"; break;
    case EQUAL: return "EQUAL"; break;
    case EQUAL_EQUAL: return "EQUAL_EQUAL"; break;
    case GREATER: return "GREATER"; break;
    case GREATER_EQUAL: return "GREATER_EQUAL"; break;
    case LESS: return "LESS"; break;
    case LESS_EQUAL: return "LESS_EQUAL"; break;
    case IDENTIFIER: return "IDENTIFIER"; break;
    case STRING: return "STRING"; break;
    case NUMBER: return "NUMBER"; break;
    case AND: return "AND"; break;
    case CLASS: return "CLASS"; break;
    case ELSE: return "ELSE"; break;
    case FALSE: return "FALSE"; break;
    case FUN: return "FUN"; break;
    case FOR: return "FOR"; break;
    case IF: return "IF"; break;
    case NIL: return "NIL"; break;
    case OR: return "OR"; break;
    case PRINT: return "PRINT"; break;
    case RETURN: return "RETURN"; break;
    case SUPER: return "SUPER"; break;
    case THIS: return "THIS"; break;
    case TRUE: return "TRUE"; break;
    case VAR: return "VAR"; break;
    case WHILE: return "WHILE"; break;
    case END_OF_FILE: return "END_OF_FILE"; break;
    default:
        break;
    }
}