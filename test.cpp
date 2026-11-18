#include <iostream>
#include <string>
using namespace std;

int main (void) {
    string input;
        for (;;) {
        cout << "> ";
        cin >> input;
        if (input == "exit") break;
        cout << "You wrote: " << input << endl; 
    }
    
}