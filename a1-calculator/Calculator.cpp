//
// Created by Alex Belokon on 08.02.16.
//

#include "Calculator.h"
#include <cmath>


void Calculator::calculation(std::string *pString) {

    clearSpaces(pString);
    if (checkForRelevancy(pString)) {
        std::cout << "Invalid expression... " << std::endl;
    } else {
        transformUnaryOperators(pString);
        postfixNotation(pString);
        std::cout << "Your expression: " << *pString;
        std::cout << " = " << st.back() << std::endl;
    }
}

bool Calculator::checkForRelevancy(std::string *pString) {
    double l = 0, r = 0;
    char ch, ch2;
    bool isBracket = false;
    for (int i = 0; i < (*pString).length(); ++i) {
        ch = (*pString)[i];
        ch == '(' ? l++ : ch == ')' ? r++ : 0;
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

void Calculator::clearSpaces(std::string *pString) {
    for (unsigned int i = 0; i < (*pString).length(); ++i) {
        if ((*pString)[i] == ' ') {
            (*pString).erase(i, 1);
            --i;
        }
    }
}

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
                st.push_back(std::atoi(number.c_str()));
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

void Calculator::process_op(std::vector<double> &st, char op) {
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
        }
    }
}

void Calculator::process_fn(std::vector<double> &st, std::vector<std::string> &fn) {
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
    } else if (f == "abs") {
        double n = std::abs(st.back());
        st.pop_back();
        st.push_back(n);
        fn.pop_back();
    }
    else if (f == "sqrt") {
        double n = sqrt(st.back());
        st.pop_back();
        st.push_back(n);
        fn.pop_back();
    } else if (f == "!") {
        double n = factorial(st.back());
        st.pop_back();
        st.push_back(n);
        fn.pop_back();
    }
}

double Calculator::factorial(double operand) {
    double result = 1;
    for (int i = 1; i <= std::abs(operand); i++) {
        result *= i;
    }
    return operand < 0 ? -result : result;
}

bool Calculator::isNumber(char ch) {
    return ((ch >= '0') && (ch <= '9')) || (ch == '.');
}

bool Calculator::isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == 'f';
}

bool Calculator::isUnaryOperator(char &ch) {
    return ch == '+' || ch == '-';
}

int Calculator::priority(char op) {
    return op == '+' || op == '-' ? 1 : op == '*' || op == '/' ? 2 : op == '^' || op == 'f' ? 3 : -1;
}

bool Calculator::isLetter(char ch) {
    return ((ch >= 97 && ch <= 122) || ch == '!');
}

bool Calculator::isFunction(std::string func) {
    return func == "sqrt" || func == "sin" || func == "cos" || func == "tan" || func == "log" || func == "abs" ||
           func == "!";
}

