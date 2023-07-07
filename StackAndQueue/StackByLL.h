#ifndef STACKBYLL_H
#define STACKBYLL_H

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

class Node {
private:
    int data{0};
    Node* next{nullptr};
public:
    // Constructors
    Node() = default;
    Node(const int _data):
        data{_data},
        next{nullptr} {}
    Node(const int _data, Node* const _next):
        data{_data},
        next{_next} {}
    
    // Delete the LL
    void deleteLL() {
        Node* current = this;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Insert at front
    Node* insertAtFront(const int element) {
        Node* head = this;
        Node* newNode = new Node(element, head);
        return newNode;
    }

    // Delete at front
    Node* deleteAtFront(int& popElem) {
        Node* head = this;
        if (head == nullptr) {
            return nullptr;
        } else {
            Node* popNode = head;
            popElem = popNode->data;
            head = head->next;
            delete popNode;
            return head;
        }
    }

    // Print the LL
    void printLL() {
        Node* current = this;
        while (current != nullptr) {
            cout << current->data << " --> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }

    // Get the head node data
    int getNodeData() const {
        return this->data;
    }
};

class StackByLL {
    Node* top{nullptr};

public:
    // Constructor
    StackByLL() = default;
    
    // Destructor
    ~StackByLL() {
        this->top->deleteLL();
        cout << "Stack is deleted!" << endl;
    }

    // Operations on Stack
    void push(const int elem) {
        this->top = this->top->insertAtFront(elem);
        cout << "Pushed " << elem << " onto stack" << endl;
    }
    int pop() {
        if (this->top == nullptr) {
            cout << "Stack Underflow!" << endl;
            return -1;
        } else {
            int popElem = 0;
            Node* newHead = this->top->deleteAtFront(popElem);
            cout << "Popped " << popElem << " from stack" << endl;
            this->top = newHead;
            return popElem;
        }
    }
    void peek() const {
        cout << "Top Node: " << this->top->getNodeData() << endl;
    }
    bool isEmpty() const {
        return this->top == nullptr;
    }
    void printStack() const {
        if (this->isEmpty()) {
            cout << "Stack is Empty!" << endl;
        } else {
            this->top->printLL();
        }
    }
};

#endif