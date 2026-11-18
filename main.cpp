#include <iostream>
#include "Lox.h"
using namespace std;

int main (int argc, char **argv) {
    if (argc > 1){
        cout << "Usage: cplox [script]\n";
        exit(64);
    } else if (argc == 1) {
        lox.runFile(argv[1]);
    } else {
        lox.runPrompt();
    }
    return 0;
}