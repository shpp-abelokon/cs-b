//
// Created by Alex Belokon on 08.02.16.
//
#include <iostream>
#include "Calculator.h"


int main() {

    std::cout << "    ---- Welcome to the calculator C++!!! ----" << std::endl;
    std::cout << "[ plus: + ] [ minus: - ] [ multiply: * ] [ divide: / ] " << std::endl;
    std::cout << "[ sinus: sin(x) ] [ cosine: cos(x) ] [ tan: tan(x) ] " << std::endl;
    std::cout << "[ square root: sqrt(x) ] [ logarithm: log(x) ]  " << std::endl;
    std::cout << "[ x in degree y: x^Y ] [ x factorial: x! ] [ variables: a,b,c ] " << std::endl;
    std::cout << "[ Close calculator C++: exit] " << std::endl << std::endl;
    Calculator *calculator = new Calculator();
    while (true) {
        std::cout << "Input your math expression: ";
        std::string input = "";
        getline(std::cin, input);
        if (input == "exit") {
            break;
        }
        calculator->calculation(&input);
    }
    delete (calculator);
    return 0;
}