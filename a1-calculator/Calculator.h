//
// Created by Alex Belokon on 08.02.16.
//

#ifndef A1_CALCULATOR_CALCULATOR_H
#define A1_CALCULATOR_CALCULATOR_H

#include "MyVector.h"
#include <map>


class Calculator {
public:

    double calculate(std::string *pString);

    bool checkString(std::string *pString);

private:
    bool isCheckExpressionValidation(std::string *pString);

    void removeSpaces(std::string *pString);

    void tolower_str(std::string *pString, int (*tolower)(int));

    void convertUnaryOperatorsExpressions(std::string *pString);

    void convertImplicitMultiplicationAndSubtraction(std::string *pString);

    bool isNumber(char ch);

    bool isOperator(char ch);

    bool isUnaryOperator(char &ch);

    void calculatePostfixNotation(std::string *pString);

    void performMathOperations(MyVector<double> &st, char op);

    int priority(char op);

    MyVector<double> st;
    MyVector<std::string> fn;
    MyVector<char> op;
    std::string number;
    std::string func;
    std::string a, b, c;

    bool isLetter(char ch);

    bool isUnary;

    bool isFunction(std::string func);

    void performMathFunctions(MyVector<double> &st, MyVector<std::string> &fn);

    double factorial(double operand);

public:
    ~Calculator() {
            MyVector<double> st;
            MyVector<char> op;
            MyVector<std::string> fn;
            std::string number;
            std::string func;
            std::string a, b, c;
            std::cout << "Memory clear..." << std::endl;
    };

    void errorMassage();

    bool isMathOperator(char ch);
};


#endif //A1_CALCULATOR_CALCULATOR_H
