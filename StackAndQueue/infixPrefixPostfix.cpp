#include <iostream>
#include "StackByArray.h"
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

void replace(string& sent, string oldWord, string newWord) {
    size_t len = sent.length();
    size_t pos = sent.find(oldWord);
    // find returns std::string::npos if not found which is mostly -1 but
    // it's better to use npos as unsigned and signed comparison has side effects

    // replace all of the occurrences
    while (pos != std::string::npos) {
        sent.replace(pos, oldWord.length(), newWord);
        pos = sent.find(oldWord);
    }
}

bool isin(string& sent, char letter) {
    size_t pos = sent.find(letter);
    if (pos == std::string::npos) {
        return false;
    } else {
        return true;
    }
}

int prio(char op) {
    int prio{0}; // Less the number, more higher is priority
    if (op == '*' || op == '/') prio = 2;
    if (op == '+' || op == '-') prio = 3;
    if (op == '^') prio = 1;
    return prio;
}

int asso(char op) {
    int asso{0}; // Less the number, more higher is priority
    if (op == '^') asso = 'R';
    else asso = 'L';
    return asso;
}

string infixToPostfix(const string* const infix) {
    string inStr{*infix};
    replace(inStr, string(" "), string(""));

    string operators = "+-*/^";
    string digits = "0123456789";
    
    StackByArray* stack = new StackByArray(inStr.length());
    string postStr{""};

    for (char c: inStr) {
        if (c == '(') {
            stack->push(c);
        } else if (isin(operators, c)) {
            // check the precedance and associativity
            if (stack->isEmpty()) {
                stack->push(c);
            } else if (stack->peek() != '(') {
                if (prio(stack->peek()) > prio(c)) {
                    stack->push(c);
                } else if (prio(stack->peek()) < prio(c)) {
                    // TODO: Fix a Bug: Recursively the input element must be compared
                    // with the top of stack as long as the prio(c) is less than prio(tos)
                    postStr += string(1, static_cast<char>(stack->pop())) + string(1,' ');
                    stack->push(c);
                } else if (prio(stack->peek()) == prio(c)) {
                    if (asso(c) == 'L') {
                        // If L to R precedance then pop first
                        postStr += string(1, static_cast<char>(stack->pop())) + string(1,' ');
                        stack->push(c);
                    } else {
                        // If R to L then push
                        stack->push(c);
                    }
                } else {
                    cout << "Something is wrong" << endl;
                }
            } else {
                stack->push(c);
            }
        } else if (isin(digits, c)) {
            postStr += string(1,c) + string(1,' ');
        } else if (c == ')') {
            while (stack->peek() != '(') {
                if (stack->isEmpty()) break;
                postStr += string(1, static_cast<char>(stack->pop())) + string(1,' ');
            }
        } else {
            cout << "Invalid symbols at input string" << endl;
        }
    }
    while (!(stack->isEmpty())) {
        if (stack->peek() == '(') {
            stack->pop();
        } else {
            postStr += string(1, static_cast<char>(stack->pop())) + string(1,' ');
        }
    }
    delete stack;
    return postStr;
}

int main() {
    string input = "((3+(2*5))-(7^(9^4)))";
    string output = infixToPostfix(&input);
    cout << "Infix: " << input << endl;
    cout << "Postfix: " << output << endl;
    return 0;
}