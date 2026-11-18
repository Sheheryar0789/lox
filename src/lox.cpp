#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "TokenType.h"
#include "Scanner.h"
#include "Lox.h"
using namespace std;
    
Lox::Lox() { hadError = false;}

void Lox::runFile(string path) {
    ifstream file(path);
    string content = "";
    
    if (!file.is_open()){
        cerr << "Failed to open file: " << path << endl;
        return;
    } 

    string line;
    while (getline(file, line)) {
        content = content + line;
        // cout << line << endl; por solo debugging
    }
    file.close();
    
    run(content);
    if (hadError) exit(65);
    return;
}

void Lox::runPrompt() {
    string input;
    for (;;) {
        cout << "> ";
        cin >> input;
        if (input == "exit") break;
        run(input);
        hadError = false;
    }
}

void Lox::run(string source) {
    // initialize scanner class obj and list of Token (another object)
    Scanner scanner(source);
    list<Token> tokens = scanner.scanTokens();
    
    for (Token token : tokens) {
            cout << token.toString() << " ";
        }
}

void Lox::error(int line, string message) {
    report(line, "", message);
}

void Lox::report (int line, string where, string message){
    cerr << "[line " << line << "] Error " << where << ":" << message << endl;
    hadError = true;
}
        
    
