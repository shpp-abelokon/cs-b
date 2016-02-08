//
// Created by Alex Belokon on 08.02.16.
//

#ifndef A1_CALCULATOR_CALCULATOR_H
#define A1_CALCULATOR_CALCULATOR_H

#pragma once /* Защита от двойного подключения заголовочного файла */
#include <string>
#include <vector>
#include <iostream>

class Calculator {
public:

    void calculation(std::string *pString);

private:
    bool checkForRelevancy(std::string *pString);
    void clearSpaces(std::string *pString);
    void transformUnaryOperators(std::string *pString);
    bool isNumber(char ch);
    bool isOperator(char ch);
    bool isUnaryOperator(char &ch);
    void postfixNotation(std::string *pString);
    void process_op(std::vector<double> &st, char op);
    int priority (char op);
    std::vector<double> st;
    std::vector<char> op;
    std::string number;
    bool isUnary;

public:
    ~Calculator() {
        std::vector<double> st;
        std::vector<char> op;
        std::string number;
        std::clog<<"Memory clear..."<<std::endl;
    };
};


#endif //A1_CALCULATOR_CALCULATOR_H
