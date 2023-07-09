#ifndef STACKBYARRAY_H
#define STACKBYARRAY_H

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

class StackByArray {
    private:
        int max;
        int* array; // Dynamically allocated
        int top{-1};
    
    public:
        // Constructors
        StackByArray(const int _max):
            max{_max},
            array{new int[_max]()} {} // Initializes all element as 0
        StackByArray():
            max{10},
            array{new int[max]()} {} // Initializes all element as 0
        StackByArray(StackByArray* other) {
            this->max = other->max;
            this->top = other->top;
            this->array = new int[this->max]();
            for (int i = 0; i < this->max; i++) {
                this->array[i] = other->array[i];
            }
        }

        // Destructor
        ~StackByArray() {
            delete[] array; // For statically allocated Stack object, it is auto deleted
            cout << "Stack is deleted!" << endl;
        }

        // Checking state of stack
        bool isEmpty() const {
            return this->top == -1;
        }
        bool isFull() const {
            return this->top == this->max - 1;
        }
        void printStack() {
            if (isEmpty()) {
                cout << "Stack Underflow!" << endl;
            } else {
                int current = this->top;
                while (current != -1) {
                    cout << this->array[current] << " --> ";
                    current--;
                }
                cout << "END of Stack" << endl;
            }
        }

        // Performing operations on stack
        void push(const int elem) {
            if (this->isFull()) {
                cout << "Stack Overflow!" << endl;
            } else {
                (this->top)++;
                this->array[this->top] = elem;
                // cout << "Pushed " << elem << " onto stack" << endl;
            }
        }
        int pop() {
            if (this->isEmpty()) {
                cout << "Stack Underflow!" << endl;
                return -1;
            } else {
                int poppedElem = this->array[this->top];
                this->array[this->top] = 0;
                (this->top)--;
                // cout << "Popped " << poppedElem << " from stack" << endl;
                return poppedElem;
            }
        }
        int peek() {
            if (this->isEmpty()) {
                // cout << "Stack Underflow!" << endl;
                return -1;
            } else {
                // cout << "Top element of stack: " << this->array[this->top] << endl;
                return this->array[this->top];
            }
        }

};

#endif