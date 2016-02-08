//
// Created by Alex Belokon on 08.02.16.
//
#include <iostream>
#include "Calculator.h"

int main() {
    Calculator *calculator = new Calculator();

    while(true) {
        std::cout <<"Input your math expression: ";
        std::string input;
        getline(std::cin, input);
        if(input.empty ()) {
            break;
        }
        calculator->calculation(&input);
    }
    delete(calculator);
    return 0;
}