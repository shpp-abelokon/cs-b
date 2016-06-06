//
// Created by Alex Belokon on 08.02.16.
//
#include <iostream>
#include "Calculator.h"
#include "UnitTest.h"

#define DEBUG true

using namespace std;

void displayGreeting();

void result(string *pString, Calculator *calculator);

void runTest();

int main() {

    displayGreeting();

    if (DEBUG) runTest();
    else {
        Calculator *calculator = new Calculator();
        while (true) {
            string input = "";
            cout << "Input your math expression: ";
            getline(cin, input);
            if (input == "exit"){
                break;
            }
            else if (calculator->checkString(&input)){
                result(&input, calculator);
            }
        }
    }
    return 0;
}

void runTest() {
    UnitTest *testing = new UnitTest();
    testing->runTest();
}

void result(string *pString, Calculator *calculator) {
    cout << "Your expression: " << *pString << " = " << calculator->calculate(pString) << endl;
}

void displayGreeting() {
    cout << "    ---- Welcome to the calculator C++!!! ----" << endl;
    cout << "[ plus: + ] [ minus: - ] [ multiply: * ] [ divide: / ] " << endl;
    cout << "[ sinus: sin(x) ] [ cosine: cos(x) ] [ tan: tan(x) ] " << endl;
    cout << "[ square root: sqrt(x) ] [ logarithm to the base 2 numbers: log(x) ]  " << endl;
    cout << "[ x in degree y: x^Y ] [ x factorial: x! ] [ variables: a,b,c ] " << endl;
    cout << "[ Close calculator C++: exit] " << endl << endl;
}