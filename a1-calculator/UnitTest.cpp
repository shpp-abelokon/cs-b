//
// Created by alex on 16.02.16.
//

#include "UnitTest.h"
#include "Calculator.h"

void UnitTest::runTest() {

    test("2 + 2", 4);
    test("(2+4)*3", 18);
    test("(2+4)(2+4)", 36);
    test("2(2^4)/3", 10.6667);
    test("-2+6", 4);
    test("(-5  + 1)^-2", 0.0625);
    test("----2 +----(4/2)+ sIn(2)*(2^3)", 11.2744);
    test("5!+(----2 *3)cos(2)+---5 * sQrt(2^2)", 107.503);
    test("Log(5)+10", 12.3219);
    test("(sin(3)+20*10)", 200.141);
    test("2^3+(4*(-2))", 0);
    test("2-(-2)", 4);
    test("27/3^3", 1);
    test("(Sin(2)+5!)^3/2", 883790);
    test("sQrt(81+8)", 9.43398);
    test("(4!-5) * ------sqrt(36)", 114);
    test("sqrt((89-8))", 9);
    test("sqrt(8*(3-1))", 4);
    test("(sqrt(36) + sqrt(81)-10/2sIn(5-1))", 18.784);
    test("sin(5+4/8)", -0.70554);
    test("cos(10)", -0.839072);
    test("tan(4.5)", 4.63733);
    test("3!", 6);
    test("(7-2)*sqrt(8)+(((---1.5+3.77)-8!)+10)/sin(3.3)", 255538);
    test("sin(5)/3+21-(32+cos(3)*2.5/(cos(21)/3))", -24.8755060896);
    test("-34-(-9)*(2^4)/(sin(23^2)*sqrt(4^2))", 4.44213062604);
    test("3 * sin(420)  + cos((255+13)/10)", -2.5767);
    test("5+5*3-(((123+12)*3)/13)", -11.1538);
    test("-5+6*12*(2+8)", 715);
    test("sin3*cos3/3-tan4", -1.204390532);
    test("2+-3+5--6/-6*-9+4--3+9-7", 22);
    test("----16(--Sin(4-1))+--tan(2)*---5(2+2.2)/--5!*(-0.5/-1.5)+-24---100", -121.615);
}

void UnitTest::test(std::string test, double res) {

    Calculator *calculator = new Calculator();
    calculator->checkingString(&test);
    double result = calculator->calculation(&test);
    std::cout << test << " = " << calculator->calculation(&test) << " / " << res << std::endl;

}