#ifndef STACKBYQUEUE_H
#define STACKBYQUEUE_H

#include <iostream>
#include "QueueByArray.h"

using std::cout;
using std::cin;
using std::endl;

class StackByQueue {
    CircularQ* q1{nullptr};
    CircularQ* q2{nullptr};

public:
    StackByQueue(int _max) {
        this->q1 = new CircularQ(_max);
        this->q2 = new CircularQ(_max);
    }
    ~StackByQueue() {
        delete this->q1;
        delete this->q2;
    }

    bool isEmpty() {
        return (this->q1->isEmpty() && this->q2->isEmpty());
    }
    bool isFull() {
        return (this->q1->isFull() || this->q2->isFull());
    }
    void push(int elem) {
        if (this->isFull()) {
            cout << "Cannot push anymore, the stack is full!" << endl;
        } else if (this->q1->isEmpty() && !(this->q2->isEmpty())) {
            this->q2->enq(elem);
        } else if (this->q2->isEmpty() && !(this->q1->isEmpty())) {
            this->q1->enq(elem);
        } else if (this->isEmpty()) {
            this->q1->enq(elem); // q1 or q2 anything is fine here 
        } else {
            cout << "2 queues cannot be non-empty at same time" << endl;
        }
    }

    CircularQ* copyQueue(CircularQ* srcQueue) {
        // srcQueue->printQ();
        CircularQ* dstQueue = new CircularQ(srcQueue);
        // dstQueue->printQ();
        return dstQueue;
    }
    int len(CircularQ* srcQueue) {
        CircularQ* q = copyQueue(srcQueue);
        int length = 0;
        while (!(q->isEmpty())) {
            length++;
            q->deq();
        }
        delete q;
        return length;
    }
    void print() {
        if (this->isEmpty()) {
            cout << "EMPTY STACK" << endl;
        } else {
            // We create the copy of q1 and q2
            CircularQ* q1copy = this->copyQueue(this->q1);
            CircularQ* q2copy = this->copyQueue(this->q2);
            int len1 = this->len(q1copy);
            int len2 = this->len(q2copy);
            
            int* arr = new int[len1+len2]();
            int j = 0;
            while (!(len1 == 0 && len2 == 0)) {
                if (len2 == 0) {
                    for (int i = 0; i < len1-1; i++) {
                        q2copy->enq(q1copy->deq());
                    }
                    arr[j] = q1copy->deq();
                    len1 = this->len(q1copy);
                    len2 = this->len(q2copy);
                } else if (len1 == 0) {
                    for (int i = 0; i < len2-1; i++) {
                        q1copy->enq(q2copy->deq());
                    }
                    arr[j] = q2copy->deq();
                    len1 = this->len(q1copy);
                    len2 = this->len(q2copy);
                } else {
                    cout << "Error: 2 queues cannot be non-empty at same time" << endl;
                }
                j++;
            }
            
            for (int i = 0; i < j; i++) {
                cout << arr[i] << " --> ";
            }
            cout << "END of STACK" << endl;

            delete[] arr;
            delete q1copy;
            delete q2copy;
        }
    }

    int pop() {
        if (this->isEmpty()) {
            cout << "Cannot pop anymore, Stack is already empty" << endl;
            return 0;
        } else if (this->q1->isEmpty() && (!(this->q2->isEmpty()))) {
            int len2 = this->len(this->q2);
            for (int i = 0; i < len2-1; i++) {
                this->q1->enq(this->q2->deq());
            }
            return this->q2->deq();
        } else if (this->q2->isEmpty() && (!(this->q1->isEmpty()))) {
            int len1 = this->len(this->q1);
            for (int i = 0; i < len1-1; i++) {
                this->q2->enq(this->q1->deq());
            }
            return this->q1->deq();
        } else {
            cout << "Something is wrong" << endl;
            return 0;
        }
    }

};

#endif