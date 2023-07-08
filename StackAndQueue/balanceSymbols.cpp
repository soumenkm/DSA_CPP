#include <iostream>
#include "StackByArray.h"

using std::cout;
using std::cin;
using std::endl;

bool isBalanced(const char* const array) {
    StackByArray* stack = new StackByArray(100);
    bool res{false};
    int i = 0;
    for (; array[i] != '\0'; i++) {
        if ((array[i] == '{') || (array[i] == '[') || (array[i] == '(')) {
            // For opening type symbols, push it in stack
            stack->push(array[i]);
        } else if ((array[i] == '}') || (array[i] == ']') || (array[i] == ')')) {
            // For closing type symbols, pop it from the stack
            if (stack->isEmpty()) {
                // Stack is empty means the input is not finished but somehow
                // stack became empty implying that unbalanced symbols
                res = false;
                cout << "Unbalanced symbol at " << i << "-th position '"
                    << array[i] << "' for the input sequence - " << array << endl;
                delete stack; // Free up the heap memory
                return res;
            } else {
                // Popped out symbol does not match with input symbol so unbalanced
                char pop = stack->pop();
                if ((array[i] == '}') && (pop == '{')) {
                    continue;
                } else if ((array[i] == ']') && (pop == '[')) {
                    continue;
                } else if ((array[i] == ')') && (pop == '(')) {
                    continue;
                } else {
                    res = false;
                    cout << "Unbalanced symbol at " << i << "-th position '"
                        << array[i] << "' for the input sequence - " << array << endl;
                    delete stack; // Free up the heap memory
                    return res;
                }               
            } 
        } else {
            cout << "Invalid input symbols other than '(', ')', '[', ']', '{', '}'" << endl;
            res = false;
            delete stack; // Free up the heap memory
            return res;
        }
    }
    if (!(stack->isEmpty())) {
        // Input is ended but the satck is not empty means unbalanced symbols
        res = false;
    } else {
        // Input is ended and stack is empty without any error means it is balanced
        res = true;
    }
    if (res) {
        cout << "Balanced Symbols" << endl;
    } else {
        cout << "Unbalanced symbol at " << i << "-th position '"
             << array[i] << "' for the input sequence - " << array << endl;
    }

    delete stack; // Free up the heap memory
    return res;
}

int main() {
    char seq1[] = "(({}{}))}";

    isBalanced(seq1);

    return 0;
}