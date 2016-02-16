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

    void transform_str(std::string *pString, int (*tolower)(int));

    void transformUnaryOperators(std::string *pString);

    void correctRecordMinusAndMultiplication(std::string *pString);

    bool isNumber(char ch);

    bool isOperator(char ch);

    bool isUnaryOperator(char &ch);

    void postfixNotation(std::string *pString);

    void process_op(std::vector<double> &st, char op);

    int priority(char op);

    std::vector<double> st;
    std::vector<std::string> fn;
    std::vector<char> op;
    std::string number;
    std::string func;
    std::string a, b, c;

    bool isLetter(char ch);

    bool isUnary;

    bool isFunction(std::string func);

    void process_fn(std::vector<double> &st, std::vector<std::string> &fn);

    double factorial(double operand);

public:
    ~Calculator() {
        std::vector<double> st;
        std::vector<char> op;
        std::vector<std::string> fn;
        std::string number;
        std::string func;
        std::string a, b, c;
        std::cout << "Memory clear..." << std::endl;
    };

};


#endif //A1_CALCULATOR_CALCULATOR_H
