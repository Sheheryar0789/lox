#pragma once
#include "TokenType.h"
using namespace std;

class Lox {
    public:
    inline static bool hadError = false;
    
    Lox();
    void runFile(string path);
    void runPrompt();
    void run(string source);
    void error(int line, string message);
    void report (int line, string where, string message);
        
};
     
extern Lox lox;