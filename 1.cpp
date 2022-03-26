#include <iostream>
#include <stack>
#include <map>
#include <string>
using namespace std;

class PostfixNotation {
public:
    static string toPostfixNotation(const string& expr);
    static double calculatePostfixExpression(const string& expr);
};

map<char, int> operations = { {'+', 0}, {'-', 0},  {'*', 1}, {'/', 1} };
string PostfixNotation::toPostfixNotation(const string& expr) {
    stack<char> stack;
    string result;
    for (const auto& i : expr) {
        if (isdigit(i)) {
            result += i;
            continue;
        }
        if (operations.find(i) != operations.end()) {
            if (stack.empty() || stack.top() == '(') {
                stack.push(i);
                continue;
            }
            if ((operations.find(stack.top()) != operations.end()) && operations[i] > operations[stack.top()]) {
                stack.push(i);
                continue;
            }
            if ((operations.find(stack.top()) != operations.end()) && operations[i] <= operations[stack.top()]) {
                while ((operations.find(stack.top()) != operations.end() && operations[i] <= operations[stack.top()]) || stack.top() != '(') {
                    result += stack.top();
                    stack.pop();
                    if (stack.empty())
                        break;
                }
                stack.push(i);
                continue;
            }
        }
        if (i == '(') {
            stack.push(i);
            continue;
        }
        if (i == ')') {
            while (stack.top() != '(') {
                result += stack.top();
                stack.pop();
            }
            stack.pop();
        }
    }
    while (!stack.empty()) {
        result += stack.top();
        stack.pop();
    }
    return result;
}

double PostfixNotation::calculatePostfixExpression(const string& expr) {
    stack<string>stack;
    for (const auto& i : expr) {
        if (isdigit(i)) {
            stack.push(string(1, i));
            continue;
        }
        if (operations.find(i) != operations.end()) {
            auto second = stod(stack.top());
            stack.pop();
            auto first = stod(stack.top());
            stack.pop();
            if (i == '*')
                stack.push(to_string(first * second));
            if (i == '/')
                stack.push(to_string(first / second));
            if (i == '-')
                stack.push(to_string(first - second));
            if (i == '+')
                stack.push(to_string(first + second));
        }
    }
    return stod(stack.top());
}


int main()
{
    string postfix = PostfixNotation::toPostfixNotation("((2+1)*3+5)*(1+1)");
    cout << postfix << endl;
    double result = PostfixNotation::calculatePostfixExpression(postfix);
    cout << result;
}