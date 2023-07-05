#include "Node.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void printCLL(Node* const cllHead) {
    if (cllHead == nullptr) {
        Node::printSLL(cllHead);
    } else {
        Node* current = cllHead->next;
        cout << cllHead->data << " --> ";
        while (current != cllHead) {
            cout << current->data << " --> ";
            current = current->next;
        }
        cout << current->data << " --> ... " << endl;
    }
}

int lenCLL(Node* const cllHead) {
    if (cllHead == nullptr) {
        cout << "Length of CLL is: 0" << endl;
        return 0;
    } else {
        Node* current = cllHead;
        int len = 0;
        while (current->next != cllHead) {
            current = current->next;
            len++;
        }
        len++;
        cout << "Length of CLL is: " << len << endl;
        return len;
    }
}

Node* convertSLLtoCLL(Node* const sllHead) {
    if (sllHead == nullptr) {
        Node::printSLL(sllHead);
        return nullptr;
    } else {
        Node* const cllHead = sllHead;
        Node* current = cllHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = cllHead;
        printCLL(cllHead);
        return cllHead;
    }
}

int main() {
    int arr1[] = {10,20,30,40,50}; int s1 = sizeof(arr1)/sizeof(int);
    Node* head1 = Node::buildSLLfromArray(arr1, s1);
    Node* head2 = convertSLLtoCLL(head1);
    lenCLL(head2);
    return 0;
}