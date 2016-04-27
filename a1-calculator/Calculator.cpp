//
// Created by abelokon on 08.02.16.
// File: Calculator.cpp
// Author abelokon
//

#include <iostream>
#include <cmath>
#include "Calculator.h"

/*
 *  Check validity of the input string.
 *  @return bool
 */
bool Calculator::checkingString(std::string *pString) {
    clearSpaces(pString);
    transform_str(pString, tolower);
    if (checkValidity(pString)) {
        std::cout << "Invalid expression... " << std::endl;
        return false;
    }
    return true;
}

/*
 *  The count of the incoming expression
 *  @return double result - the result of the expression
 */
double Calculator::calculation(std::string *pString) {
    double result;
    transformUnaryOperators(pString);
    postfixNotation(pString);
    result = st.back();
    st.pop_back();
    return result;
}

/*
 *  Verification of the mathematical expression for invalid characters and character combinations,
 *  and the right number of parentheses.
 *  @return bool
 */
bool Calculator::checkValidity(std::string *pString) {
    double l = 0, r = 0;
    char ch, ch2;
    bool isBracket = false;
    std::string func2;
    for (int i = 0; i < (*pString).length(); ++i) {
        ch = (*pString)[i];
        ch == '(' ? l++ : ch == ')' ? r++ : 0;
        if (isLetter(ch)) {
            func2 += ch;
        } else {
            if (!func2.empty() && !isFunction(func2)) {
                return true;
            }
            func2 = "";
        }
        if (ch == '(') {
            isBracket = true;
        }
        if (ch == ')' && !isBracket) {
            return true;
        }
        if (i == 0) {
            if (ch == '*' || ch == '/' || ch == '^' || ch == '!' || ch == ')') {
                return true;
            }
            if (ch == '+' && (*pString)[i + 1] == '+') {
                return true;
            }
        }
        if (i == (*pString).length() - 1) {
            if (ch == '*' || ch == '/' || ch == '^' || ch == '+' || ch == '-' || ch == '(') {
                return true;
            }
        }
        if (i != 0 && i != (*pString).length()) {
            ch2 = (*pString)[i - 1];
            if (ch == '*' || ch == '/' || ch == '^' || ch == '!') {
                if (isOperator(ch2)) {
                    return true;
                }
            }
            if (i > 2 && ch == '+' && ch2 == '+' && (*pString)[i - 2] == '+') {
                return true;
            }
        }
    }
    return l - r != 0;
}

/*
 *  Remove gaps in mathematical formula
 */
void Calculator::clearSpaces(std::string *pString) {
    for (unsigned int i = 0; i < (*pString).length(); ++i) {
        if ((*pString)[i] == ' ') {
            (*pString).erase(i, 1);
            --i;
        }
    }
}

/*
 *  Transform unary operators in expressions
 */
void Calculator::transformUnaryOperators(std::string *pString) {
    correctRecordMinusAndMultiplication(pString);
    isUnary = false;
    std::string tempString = *pString;
    *pString = "";
    for (unsigned int i = 0; i < tempString.length(); ++i) {
        char ch = tempString[i];
        if (isUnaryOperator(ch) && (i == 0 || tempString[i - 1] == '('
                                    || isOperator(tempString[i - 1]))) {
            *pString += "(0";
            isUnary = true;
            *pString += ch;
        } else if (isUnary && (!isNumber(ch) || i == tempString.length() - 1)) {
            (i == tempString.length() - 1) ? (*pString = *pString + ch + ')') : *pString = *pString + ')' + ch;
            isUnary = false;
        } else {
            *pString += ch;
        }
    }
}

/*
 *  Convert record to correct the minuses and implicit multiplication
 */
void Calculator::correctRecordMinusAndMultiplication(std::string *pString) {
    std::string tempString = *pString;
    *pString = "";
    for (unsigned int i = 0; i < tempString.length(); ++i) {
        char ch = tempString[i];
        char ch2 = tempString[i + 1];
        if (ch == '-' && ch2 == '-') {
            (i == 0 || isOperator(tempString[i - 1]) || tempString[i - 1] == '(') ? i++ : (*pString += '+', i++);
        } else if (ch == ')' && ch2 != '!' && (isLetter(ch2) || isNumber(ch2))) {
            *pString += ch;
            *pString += '*';
        } else if (i > 0 && ch == '(' && (isNumber(tempString[i - 1])
                                          || tempString[i - 1] == '!' || tempString[i - 1] == ')')) {
            *pString += '*';
            *pString += ch;

        } else if (ch == '!' && isNumber(ch2)) {
            *pString += ch;
            *pString += '*';
        } else if (isNumber(ch) && ch2 != '!' && isLetter(ch2)) {
            *pString += ch;
            *pString += '*';
        } else {
            (*pString += ch);
        }
    }
}

/*
 *  Produce a calculation expression using Postfix notation
 */
void Calculator::postfixNotation(std::string *pString) {
    for (unsigned int i = 0; i < (*pString).length(); ++i) {
        char ch = (*pString)[i];
        if ((isLetter(ch) || (isOperator(ch) || ch == '(' || ch == ')')) && number != "") {
            st.push_back(std::atof(number.c_str()));
            number = "";
        }
        if (isOperator(ch)) {
            while (!op.empty() && priority(ch) <= priority(op.back())) {
                process_op(st, op.back());
                op.pop_back();
            }
            op.push_back(ch);
        } else if (isNumber(ch)) {
            number += ch;
            if (i == (*pString).length() - 1) {
                st.push_back(std::atof(number.c_str()));
                number = "";
            }
        } else if (ch == '(') {
            op.push_back('(');
        } else if (ch == ')') {
            while (op.back() != '(') {
                process_op(st, op.back());
                op.pop_back();
            }
            op.pop_back();
        } else if (isLetter(ch)) {
            func += ch;
            if (i == (*pString).length() - 1 || !isLetter((*pString)[i + 1])) {
                fn.push_back(func);
                op.push_back('f');
                func = "";
            }
        }
    }
    while (!op.empty()) {
        process_op(st, op.back());
        op.pop_back();
    }
}

/*
 *  Perform mathematical operations: +, -, *, /, ^, f
 */
void Calculator::process_op(myVector<double> &st, char op) {
    if (op == 'f') {
        process_fn(st, fn);
    } else {
        double r = st.back();
        st.pop_back();
        double l = st.back();
        st.pop_back();
        switch (op) {
            case '+':
                st.push_back(l + r);
                break;
            case '-':
                st.push_back(l - r);
                break;
            case '*':
                st.push_back(l * r);
                break;
            case '/':
                st.push_back(l / r);
                break;
            case '^':
                st.push_back(pow(l, r));
                break;
            default:
                break;
        }
    }
}

/*
 *  Performed mathematical functions: sin, cos, tan, log, sqrt, "!" and variables of the equation: a,b,c
 */
void Calculator::process_fn(myVector<double> &st, myVector<std::string> &fn) {
    std::string f = fn.back();
    if (f == "sin") {
        double n = sin(st.back());
        st.pop_back();
        st.push_back(n);
        fn.pop_back();
    } else if (f == "cos") {
        double n = cos(st.back());
        st.pop_back();
        st.push_back(n);
        fn.pop_back();
    } else if (f == "tan") {
        double n = tan(st.back());
        st.pop_back();
        st.push_back(n);
        fn.pop_back();
    } else if (f == "log") {
        double n = log2(st.back());
        st.pop_back();
        st.push_back(n);
        fn.pop_back();
    } else if (f == "sqrt") {
        double n = sqrt(st.back());
        st.pop_back();
        st.push_back(n);
        fn.pop_back();
    } else if (f == "!") {
        double n = factorial(st.back());
        st.pop_back();
        st.push_back(n);
        fn.pop_back();
    } else if (f == "a") {
        if (a.empty()) {
            std::cout << "Enter the value of the variable: a = ";
            getline(std::cin, a);
        }
        st.push_back(std::atof(a.c_str()));
        fn.pop_back();
    } else if (f == "b") {
        if (b.empty()) {
            std::cout << "Enter the value of the variable: b = ";
            getline(std::cin, b);
        }
        st.push_back(std::atof(b.c_str()));
        fn.pop_back();
    } else if (f == "c") {
        if (c.empty()) {
            std::cout << "Enter the value of the variable: c = ";
            getline(std::cin, c);
        }
        st.push_back(std::atof(c.c_str()));
        fn.pop_back();
    }
}

/* Performed mathematical functions  - factorial
 * @return double result -  factorial
 */
double Calculator::factorial(double operand) {
    double result = 1;
    for (int i = 1; i <= std::abs(operand); i++) {
        result *= i;
    }
    return operand < 0 ? -result : result;
}

/* Check the numbers from to 9 including the symbol "." */
bool Calculator::isNumber(char ch) {
    return ((ch >= '0') && (ch <= '9')) || (ch == '.');
}

/* Check for operators: +, -, *, /, ^, f  */
bool Calculator::isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == 'f';
}

/* Check for unary operators: + and -  */
bool Calculator::isUnaryOperator(char &ch) {
    return ch == '+' || ch == '-';
}

/* The priorities of operators */
int Calculator::priority(char op) {
    return op == '+' || op == '-' ? 1 : op == '*' || op == '/' ? 2 : op == '^' || op == 'f' ? 3 : -1;
}

/* Check for characters */
bool Calculator::isLetter(char ch) {
    return ((ch >= 97 && ch <= 122) || ch == '!');
}

/* Check functions */
bool Calculator::isFunction(std::string func) {
    return func == "sqrt" || func == "sin" || func == "cos" || func == "tan" || func == "log" || func == "!" ||
           func == "a" || func == "b" || func == "c";
}

/* Converts all letters in lowercase letters */
void Calculator::transform_str(std::string *pString, int (*tolower)(int)) {
    for (int i = 0; i < (*pString).length(); ++i) {
        char res = (*pString)[i];
        (*pString)[i] = (char) tolower(res);
    }
}
