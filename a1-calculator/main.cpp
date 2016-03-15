//
// Created by Alex Belokon on 08.02.16.
//
#include <iostream>
#include "Calculator.h"
#include "UnitTest.h"
#define DEBUG true

int main() {
    std::cout << "    ---- Welcome to the calculator C++!!! ----" << std::endl;
    std::cout << "[ plus: + ] [ minus: - ] [ multiply: * ] [ divide: / ] " << std::endl;
    std::cout << "[ sinus: sin(x) ] [ cosine: cos(x) ] [ tan: tan(x) ] " << std::endl;
    std::cout << "[ square root: sqrt(x) ] [ logarithm to the base 2 numbers: log(x) ]  " << std::endl;
    std::cout << "[ x in degree y: x^Y ] [ x factorial: x! ] [ variables: a,b,c ] " << std::endl;
    std::cout << "[ Close calculator C++: exit] " << std::endl << std::endl;
    if (DEBUG) {
        unsigned int start_time =  clock();
        UnitTest *testing = new UnitTest();
        testing->runTest();
        delete (testing);
        unsigned int end_time = clock();
        unsigned int search_time = end_time - start_time; // time spent in debug
        std::cout<<"Time spent in debug:"<<(double)search_time/1000<<"s"<<std::endl;
    } else {
        Calculator *calculator = new Calculator();
        while (true) {
            std::string input = "";
            std::cout << "Input your math expression: ";
            getline(std::cin, input);
            if (input == "exit") {
                break;
            }
            if (calculator->checkingString(&input)) {
                std::cout << "Your expression: " << input << " = " << calculator->calculation(&input) << std::endl;
            }
        }
        delete (calculator);
    }
    return 0;
}