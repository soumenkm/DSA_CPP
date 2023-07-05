#include "Node.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

Node* insertNodeAtBegin(Node* const head, int _data) {
    Node* newHead = new Node(_data, head);
    Node::printSLL(newHead);
    return newHead;
}

Node* insertNodeAtEnd(Node* const head, int _data) {
    Node* current = head;
    if (current == nullptr) {
        // Corner case - LL is empty
        Node* newNode = new Node(_data);
        Node::printSLL(newNode);
        return newNode;
    } else {
        while (current->next != nullptr) {
            current = current->next;
        }
        Node* newNode = new Node(_data);
        current->next = newNode;
        Node::printSLL(head);
        return head;
    }
}

Node* insertNodeBefore(Node* const head, int targetNodeData, int newNodedata) {
    Node* current = head;

    if (current == nullptr) {
        // Corner case - LL is empty, targetNodeData can be anything
        Node* newNode = new Node(newNodedata);
        Node::printSLL(newNode);
        return newNode;
    } else if (current->next == nullptr) {
        // Corner case - LL has only 1 node, targetNodeData can be anything
        Node* newNode = new Node(newNodedata, current);
        Node::printSLL(newNode);
        return newNode;
    } else {
        while ((current->next)->data != targetNodeData) {
            current = current->next;
        }
        Node* target = current->next;
        Node* newNode = new Node(newNodedata, target);
        current->next = newNode;
        Node::printSLL(head);
        return head;
    }
}


int main() {
    int arr1[] = {10,20,30,40,50,60}; int s1 = sizeof(arr1)/sizeof(int);
    Node* head1 = Node::buildSLLfromArray(arr1, s1);
    Node* head2 = insertNodeBefore(head1, 40, 35);

    return 0;
}