#ifndef QUEUEBYSTACK_H
#define QUEUEBYSTACK_H

#include <iostream>
#include "StackByArray.h"

using std::cout;
using std::cin;
using std::endl;

class QueueByStack {
    StackByArray* s1{nullptr};
    StackByArray* s2{nullptr};
public:
    QueueByStack(int _max) {
        this->s1 = new StackByArray(_max);
        this->s2 = new StackByArray(_max);
    }
    ~QueueByStack() {
        delete this->s1;
        delete this->s2;
    }

    void transfer() {
        if (!(this->s2->isEmpty())) {
            cout << "Sorry! Transfer not possible as S2 is not empty" << endl;
        } else if (this->s1->isEmpty()) {
            cout << "Nothing to transfer as S1 is already empty" << endl;
        } else {
            while (!(this->s1->isEmpty())) {
                int popElem = this->s1->pop();
                this->s2->push(popElem);
            }
        }
    }

    bool isFull() {
        if (this->s1->isFull()) {
            if (this->s2->isEmpty()) {
                this->transfer();
                return false;
            } else {
                return true;
            }
        } else {
            return false;
        }
    }

    bool isEmpty() {
        return (this->s1->isEmpty() && this->s2->isEmpty());
    }

    void enq(int elem) {
        if (this->isFull()) {
            cout << "Cannot enqueue anymore, it is already full" << endl;
        } else {
            this->s1->push(elem);
        }
    }

    int deq() {
        if (this->isEmpty()) {
            cout << "Cannot dequeue, it is already empty" << endl;
            return 0;
        } else {
            this->transfer();
            return this->s2->pop();
        }
    }

    void peek() {
        cout << "Front: " << this->s1->peek() << " and " << 
            " Rear: " << this->s2->peek() << endl;
    }

    StackByArray* copyStack(StackByArray* srcStack) {
        // srcStack->printStack();
        StackByArray* dstStack = new StackByArray(srcStack);
        // dstStack->printStack();
        return dstStack;
    }

    void print() {
        if (this->isEmpty()) {
            cout << "EMPTY QUEUE" << endl;
        } else {
            // We create the copy of s1 and s2
            StackByArray* s1copy = this->copyStack(this->s1);
            StackByArray* s2copy = this->copyStack(this->s2);

            while (!(s2copy->isEmpty())) {
                cout << s2copy->pop() << " --> ";
            }
            while (!(s1copy->isEmpty())) {
                s2copy->push(s1copy->pop());
            }
            while (!(s2copy->isEmpty())) {
                cout << s2copy->pop() << " --> ";
            }
            cout << "END of QUEUE" << endl;

            delete s1copy;
            delete s2copy;
        }
    }
};

#endif