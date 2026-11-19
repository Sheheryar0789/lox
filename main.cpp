#include <iostream>
#include "Lox.h"
using namespace std;

int main (int argc, char **argv) {
    Lox lox;
    if (argc > 2){
        cout << "Usage: cplox [script]\n";
        exit(64);
    } else if (argc == 2) {
        lox.runFile(argv[1]);
    } else {
        lox.runPrompt();
    }
    return 0;
}