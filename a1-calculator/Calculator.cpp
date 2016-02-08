//
// Created by Alex Belokon on 08.02.16.
//

#include "Calculator.h"
#include <cmath>


void Calculator::calculation(std::string *pString) {
    if (checkForRelevancy(pString)) {
        std::cout << "Invalid expression... " << std::endl;
    } else {
        clearSpaces(pString);
        transformUnaryOperators(pString);
        postfixNotation(pString);
        std::cout << "Your expression: " << *pString;
        std::cout << " = " << st.back() << std::endl;
    }
}

bool Calculator::checkForRelevancy(std::string *pString) {
    double l = 0, r = 0;
    char ch, ch2;
    for (int i = 0; i < (*pString).length(); ++i) {
        ch = (*pString)[i];
        ch2 = (*pString)[i - 1];
        ch == '(' ? l++ : ch == ')' ? r++ : 0;
        if (ch == '*' || ch == '/' || ch == '^' || ch == '!') {
            if (isOperator(ch2)) {
                return true;
            }
        }
    }
    return l - r != 0;
}

void Calculator::clearSpaces(std::string *pString) {
    for (unsigned int i = 0; i < (*pString).length(); ++i) {
        if ((*pString)[i] == ' ') {
            (*pString).erase(i, 1);
            --i;
        }
    }
}

void Calculator::transformUnaryOperators(std::string *pString) {
    isUnary = false;
    std::string tempString = *pString;
    *pString = "";

    for (unsigned int i = 0; i < tempString.length(); ++i) {
        char ch = tempString[i];
        if (isUnaryOperator(ch) && (i == 0 || tempString[i - 1] == '('
                                    || isOperator(tempString[i - 1]))) {
            if (tempString[i - 1] == '(') {
                *pString += '0';
            } else {
                *pString += "(0";
                isUnary = true;
            }
            *pString += ch;
        } else if (isUnary && (!isNumber(ch) || i == tempString.length() - 1)) {
            *pString += ch;
            *pString += ')';
            isUnary = false;
        } else {
            *pString += ch;
        }
    }
}

void Calculator::postfixNotation(std::string *pString) {

    for (unsigned int i = 0; i < (*pString).length(); ++i) {
        char ch = (*pString)[i];
        if ((isOperator(ch) || ch == '(' || ch == ')') && number != "") {
            st.push_back(std::atof(number.c_str()));
            number = "";
        }
        if (isOperator(ch)) {
            while (!op.empty() && priority(ch) <= priority(op.back())) {
                op.pop_back();
            }
            op.push_back(ch);
        }
        if (isNumber(ch)) {
            number += ch;
            if (i == (*pString).length() - 1) {
                st.push_back(std::atoi(number.c_str()));
                number = "";
            }
        }
        if (ch == '(') {
            op.push_back('(');
        }
        if (ch == ')') {
            while (op.back() != '(') {
                process_op(st, op.back());
                op.pop_back();
            }
            op.pop_back();
        }
    }
    while (!op.empty()) {
        process_op(st, op.back());
        op.pop_back();
    }
}

void Calculator::process_op(std::vector<double> &st, char op) {
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
    }
}

bool Calculator::isNumber(char ch) {
    return ((ch >= '0') && (ch <= '9')) || (ch == '.');
}

bool Calculator::isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

bool Calculator::isUnaryOperator(char &ch) {
    return ch == '+' || ch == '-';
}

int Calculator::priority(char op) {
    return op == '+' || op == '-' ? 1 : op == '*' || op == '/' ? 2 : op == '^' ? 3 : -1;
}