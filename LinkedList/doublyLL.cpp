#include "DLLNode.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

DLLNode* insertNodeAtEnd(DLLNode* const head, int _data) {
    DLLNode* current = head;
    if (current == nullptr) {
        DLLNode* newNode = new DLLNode(_data);
        DLLNode::printDLL(newNode);
        return newNode;
    }
    while (current->next != nullptr) {
        current = current->next;
    }
    DLLNode* newNode = new DLLNode(_data);
    current->next = newNode;
    newNode->prev = current;
    DLLNode::printDLL(head);
    return head;
}

DLLNode* insertNodeAtBegin(DLLNode* const head, int _data) {
    DLLNode* newNode = new DLLNode(_data);
    if (head == nullptr) {
        DLLNode::printDLL(newNode);
        return newNode;    
    } else {
        newNode->next = head;
        head->prev = newNode;
        DLLNode::printDLL(newNode);
        return newNode;
    }
}

int main() {
    int array1[] = {}; int s1 = sizeof(array1)/sizeof(int);
    DLLNode* head1 = DLLNode::buildDLLfromArray(array1, s1);
    DLLNode* head2 = insertNodeAtBegin(head1, 60);
    return 0;
}