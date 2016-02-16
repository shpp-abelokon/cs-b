//
// Created by alex on 16.02.16.
//

#ifndef A1_CALCULATOR_UNITTEST_H
#define A1_CALCULATOR_UNITTEST_H


class UnitTest {

public:
    void runTest();

private:
    void test(std::string test, double res);

public:
    ~UnitTest() {
        std::cout << "Memory clear..." << std::endl;
    };
};


#endif //A1_CALCULATOR_UNITTEST_H
