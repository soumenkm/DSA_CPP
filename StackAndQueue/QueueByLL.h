#ifndef QUEUEBYLL_H
#define QUEUEBYLL_H

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Node {
public:
    int data{0};
    Node* next{nullptr};

public:
    Node() = default;
    Node(int _data):
        data{_data},
        next{nullptr} {}
    Node(int _data, Node* _next):
        data{_data},
        next{_next} {}

    static Node* insertAfterNode(Node* const node, int elem) {
        Node* newNode = new(std::nothrow) Node(elem);
        if (node == nullptr) {
            return newNode;
        } else {
            node->next = newNode;
            return node;
        }
    }
    static Node* deleteNode(Node* const node) {
        Node* nextNode = node->next;
        delete node;
        return nextNode;
    }
};

class ListQ {
    Node* front{nullptr};
    Node* rear{nullptr};

public:
    ListQ() = default;
    ~ListQ() {
        Node* f = this->front;
        Node* r = this->rear;
        while (f != r) {
            Node* temp = f;
            f = f->next;
            delete temp;  
        }
        if (f != nullptr) delete f;
        cout << "List Queue is deleted!" << endl;
    }
    bool isEmpty() const {
        return (this->front == nullptr && this->rear == nullptr);
    }
    bool isFull() const {
        // front is null means the memory is full so new returns null
        return (this->front == nullptr && this->rear != nullptr);
    }
    void enq(const int elem) {
        if (isFull()) {
            cout << "Memory full, can't be enqueued anymore!" << endl;
            return;
        } else if (isEmpty()) {
            this->rear = Node::insertAfterNode(nullptr, elem);
            this->front = this->rear;
        } else {
            Node::insertAfterNode(this->rear, elem);
            this->rear = this->rear->next;
        }
        cout << "Enqueued " << elem << " on the queue" << endl; 
    }
    int deq() {
        if (isEmpty()) {
            cout << "Queue is already empty!" << endl;
            return 0;
        }
        int deqElem = this->front->data;
        this->front = Node::deleteNode(this->front);
        if (this->front->next == nullptr && this->rear->next == nullptr) {
            this->rear = this->front;
        }
        cout << "Dequeued " << deqElem << " from the queue" << endl; 
        return deqElem;
    }
    void peek() const {
        if (isEmpty()) cout << "Queue is empty!" << endl;
        else {
            cout << "Front: " << this->front->data << " and " <<
                "Rear: " << this->rear->data << endl;
        }
    }
    void printQ() const {
        if (isEmpty()) cout << "Queue is empty!" << endl;
        else {
            Node* f = this->front;
            Node* r = this->rear;
            while (f != r) {
                cout << f->data << " --> ";
                f = f->next;
            }
            cout << f->data << " --> NULL" << endl;
        }
    }
};

#endif