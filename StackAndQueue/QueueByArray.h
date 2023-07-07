#ifndef QUEUEBYARRAY_H
#define QUEUEBYARRAY_H

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class LinearQ {
    int front{-1};
    int rear{-1};
    const int max{0};
    int* array{nullptr};

public:
    LinearQ() = default;
    LinearQ(int _max):
        max{_max},
        array{new int[_max]()} {}
    ~LinearQ() {
        delete[] array;
        cout << "Linear Queue is deleted!" << endl;
    }

    bool isEmpty() const {
        if (this->front == -1 && this->rear == -1) {
            return true;
        } else {
            return false;
        }
    }

    bool isFull() const {
        if (this->rear == this->max-1) {
            return true;
        } else {
            return false;
        }
    }

    void enq(int const elem) {
        if (this->isFull()) {
            cout << "Queue is Full!" << endl;
            return;
        } else if (this->isEmpty()) {
            (this->rear)++;
            (this->front)++;
            this->array[this->rear] = elem;
        } else {
            (this->rear)++;
            this->array[this->rear] = elem;
        }
        cout << "Enqueued " << elem << " on the queue" << endl; 
    }

    int deq() {
        int delElem{0};
        if (this->isEmpty()) {
            cout << "Queue is Empty!" << endl;
            return delElem;
        } else if (this->front == this->rear) {
            delElem = this->array[this->front];
            this->array[this->front] = 0;
            this->front = -1;
            this->rear = -1;
        } 
         else {
            delElem = this->array[this->front];
            this->array[this->front] = 0;
            (this->front)++;
        }
        cout << "Dequeued " << delElem << " from the queue" << endl; 
        return delElem;
    }

    void printQ() const {
        int f = this->front;
        int r = this->rear;
        cout << "FRONT --> ";
        while (f != r+1 && f != -1 && r != -1) {
            cout << this->array[f] << " --> ";
            f++;
        }
        cout << "REAR" << endl;
    }

    void peek() const {
        cout << "Front is: " << this->array[this->front] << endl;
        cout << "Rear is: " << this->array[this->rear] << endl;
    }

};

class CircularQ {
    int front{-1};
    int rear{-1};
    int max{0};
    int* array{nullptr};

public:
    CircularQ() = default;
    CircularQ(int _max):
        max{_max},
        array{new int[_max]()} {}
    ~CircularQ() {
        delete[] array;
        cout << "Circular Queue is deleted!" << endl;
    }
    CircularQ (CircularQ* other) {
            this->max = other->max;
            this->front = other->front;
            this->rear = other->rear;
            this->array = new int[this->max]();
            for (int i = 0; i < this->max; i++) {
                this->array[i] = other->array[i];
            }
    }

    bool isEmpty() const {
        if (this->front == -1 && this->rear == -1) {
            return true;
        } else {
            return false;
        }
    }

    bool isFull() const {
        if ((this->rear + 1) % this->max == this->front) {
            return true;
        } else {
            return false;
        }
    }

    void enq(int const elem) {
        if (this->isFull()) {
            cout << "Queue is Full!" << endl;
            return;
        } else if (this->isEmpty()) {
            (this->rear)++;
            (this->front)++;
            this->array[this->rear] = elem;
        } else {
            this->rear = (this->rear + 1) % this->max;
            this->array[this->rear] = elem;
        }
        // cout << "Enqueued " << elem << " on the queue" << endl; 
    }

    int deq() {
        int delElem{0};
        if (this->isEmpty()) {
            cout << "Queue is Empty!" << endl;
            return delElem;
        } else if (this->front == this->rear) {
            delElem = this->array[this->front];
            this->array[this->front] = 0;
            this->front = -1;
            this->rear = -1;
        } 
         else {
            delElem = this->array[this->front];
            this->array[this->front] = 0;
            this->front = (this->front + 1) % this->max;
        }
        // cout << "Dequeued " << delElem << " from the queue" << endl; 
        return delElem;
    }

    void printQ() const {
        int f = this->front;
        int r = this->rear;
        if (isEmpty()) cout << "Queue is Empty" << endl;
        else {
            cout << "FRONT --> ";
            for (int i = f; i < r; i = (i + 1) % this->max) {
                cout << this->array[i] << " --> ";
            }
            // when f touches r then the loop breaks so we have to explicitly print the last
            // element even when queue has only 1 element (f == r) then loop is not executed
            // even once so in that case, the only element is also printed in next line
            cout << this->array[r] << " --> REAR" << endl;
        }
    }

    void peek() const {
        cout << "Front is: " << this->array[this->front] << endl;
        cout << "Rear is: " << this->array[this->rear] << endl;
    }

};

#endif