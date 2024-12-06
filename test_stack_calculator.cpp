#include <gtest/gtest.h>
#include "stack_calculator.cpp" // 테스트할 파일을 포함

// 잘못된 문자가 포함된 수식을 테스트
TEST(CalculatorTest, InvalidCharacter) {
    string input = "1+2a";
    auto result = calculate(input);
    EXPECT_FALSE(result.success);
}

// 0으로 나누기를 테스트
TEST(CalculatorTest, DivisionByZero) {
    string input = "10/0";
    auto result = calculate(input);
    EXPECT_FALSE(result.success);
}

// 기본적인 덧셈을 테스트
TEST(CalculatorTest, Addition) {
    string input = "1+2";
    auto result = calculate(input);
    EXPECT_TRUE(result.success);
    EXPECT_EQ(result.value, 3);
}

// 기본적인 곱셈을 테스트
TEST(CalculatorTest, Multiplication) {
    string input = "2*3";
    auto result = calculate(input);
    EXPECT_TRUE(result.success);
    EXPECT_EQ(result.value, 6);
}

// 복합 연산을 테스트
TEST(CalculatorTest, MixedOperations) {
    string input = "1+2*3";
    auto result = calculate(input);
    EXPECT_TRUE(result.success);
    EXPECT_EQ(result.value, 7);
}

// 잘못된 연산자를 테스트
TEST(CalculatorTest, InvalidOperator) {
    string input = "1++2";
    auto result = calculate(input);
    EXPECT_FALSE(result.success);
}

// 나눗셈과 덧셈을 테스트
TEST(CalculatorTest, DivisionAndAddition) {
    string input = "10/2+3";
    auto result = calculate(input);
    EXPECT_TRUE(result.success);
    EXPECT_EQ(result.value, 8);
}

// 뺄셈을 테스트
TEST(CalculatorTest, Subtraction) {
    string input = "4-2";
    auto result = calculate(input);
    EXPECT_TRUE(result.success);
    EXPECT_EQ(result.value, 2);
}

// 곱셈과 뺄셈을 테스트
TEST(CalculatorTest, MultiplicationAndSubtraction) {
    string input = "5*2-3";
    auto result = calculate(input);
    EXPECT_TRUE(result.success);
    EXPECT_EQ(result.value, 7);
}

// 잘못된 입력을 테스트
TEST(CalculatorTest, InvalidInput) {
    string input = "1+2*";
    auto result = calculate(input);
    EXPECT_FALSE(result.success);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}