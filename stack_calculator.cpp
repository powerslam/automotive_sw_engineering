// -*- coding: utf-8 -*-

#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct {
    bool success;
    double value;
} CalculationResult;

int menu;
string input;

bool isRightCharacter(const std::string& str) {
    cout << "str : " << str << endl;

    return std::all_of(str.begin(), str.end(), 
        [](unsigned char c) {
            return (('0' <= c && c <= '9') || c == '+' || c == '-' || c == '*' || c == '/');
        }
    );
}

CalculationResult calculate(const string& input) {
    CalculationResult result;
    result.success = false;
    result.value = 0;

    // TEST 케이스 실행할 때에는 calculate만 실행하므로 해당 로직이 필요함
    #ifdef TEST
    if(!isRightCharacter(input) || input.back() == '+' || input.back() == '-' || input.back() == '*' || input.back() == '/') {
        cout << "수식에 잘못되었습니다. 다시 시도하세요.\n";
        return result;
    }
    #endif

    vector<double> nums;
    vector<char> op;

    double a = 0, b = 0;
    nums.push_back(0);

    int numCnt = 0;
    char prev = ' ';
    for(const char& c: input) {
        if('0' <= c && c <= '9')
            nums.back() = nums.back() * 10 + (c - '0');

        else{
            if(prev == '+' || prev == '-' || prev == '*' || prev == '/'){
                result.success = false;
                return result;
            }

            if(c == '+' || c == '-') {
                while(!op.empty() && (op.back() == '*' || op.back() == '/')){
                    if(op.back() == '*'){
                        b = nums.back();
                        nums.pop_back();
                        
                        a = nums.back();
                        nums.pop_back();

                        nums.push_back(a * b);
                    }

                    else {
                        b = nums.back();
                        nums.pop_back();
                        
                        a = nums.back();
                        nums.pop_back();

                        // Division by zero
                        if(b == 0){
                            result.success = false;
                            return result;
                        }

                        nums.push_back(a / b);
                    }

                    op.pop_back();
                }
            }

            op.push_back(c);
            nums.push_back(0);
        }
        prev = c;
    }

     while(!op.empty() && (op.back() == '*' || op.back() == '/')){
        if(op.back() == '*'){
            b = nums.back();
            nums.pop_back();
            
            a = nums.back();
            nums.pop_back();

            nums.push_back(a * b);
        }

        else {
            b = nums.back();
            nums.pop_back();
            
            a = nums.back();
            nums.pop_back();

            // Division by zero
            if(b == 0){
                result.success = false;
                return result;
            }

            nums.push_back(a / b);
        }

        op.pop_back();
    }
    
    result.success = true;
    for(auto iter = op.rbegin(); iter != op.rend(); iter++){
        if(*iter == '-')
            nums.back() *= -1;

        result.value += nums.back();
        nums.pop_back();
    }

    result.value += nums[0];

    return result;
}

// TEST 케이스 실행할 때를 위한 매크로
#ifndef TEST
int main() {
    while(true){
        cout << "************************************\n";
        cout << "*          계산기 프로그램         *\n";
        cout << "*                                  *\n";
        cout << "*    1. 사칙연산     2. 나가기     *\n";
        cout << "************************************\n";

        cout << "메뉴를 선택하세요 : ";
        cin >> menu;

        if(cin.fail()) {
            cin.clear(); // cin의 에러 플래그를 클리어
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 스트림을 비움
            cout << "잘못된 입력입니다. 다시 시도하세요.\n";
            continue;
        }

        if(menu == 1) {
            cout << "본 계산기는 음이 아닌 정수에 대한 연산만을 지원합니다.\n";
            cout << "또한, 괄호 연산은 지원하지 않습니다. 참고해주세요.\n";
            cout << "띄어쓰기 없이 수식을 입력해주세요 (예시: 1+2*3) : ";
            cin >> input;
            
            if(!isRightCharacter(input) || input.back() == '+' || input.back() == '-' || input.back() == '*' || input.back() == '/') {
                cout << "수식이 잘못되었습니다. 다시 시도하세요.\n";
                continue;
            }

            const auto& result = calculate(input);
            if(!result.success) {
                cout << "잘못된 수식입니다. 다시 시도하세요.\n";
                continue;
            }

            cout << "계산 결과 : " << result.value << '\n';
        } 
        
        else if(menu == 2) {
            cout << "프로그램을 종료합니다.\n";
            break;
        } 
        
        else {
            cout << "잘못된 선택입니다. 다시 시도하세요.\n";
        }
    }

    return 0;
}
#endif
