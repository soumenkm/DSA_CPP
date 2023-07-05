#include "Node.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

Node* deleteNodeAtBegin(Node* const head) {
    if (head == nullptr) {
        // Corner case - LL is empty
        Node* current = nullptr;
        Node::printSLL(current);
        return current;
    } else {
        Node* current = head;
        current = current->next;
        
        Node* pop = head;
        cout << "The deleted node: " << pop->data << endl;
        delete pop;

        Node::printSLL(current);
        return current;
    }
}

Node* deleteNodeAtEnd(Node* const head) {
    if (head == nullptr) {
        // Corner case - LL is empty
        Node* current = nullptr;
        Node::printSLL(current);
        return current;
    } else if (head->next == nullptr) {
        // Corner case - LL has only 1 node
        Node* current = head;
        cout << "The deleted node: " << current->data << endl;
        delete current;
        current = nullptr;
        Node::printSLL(current);
        return current;
    } else {
        Node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        cout << "The deleted node: " << current->next->data << endl;
        delete current->next;
        current->next = nullptr;
        Node::printSLL(head);
        return head;
    }
}

Node* deleteTargetNode(Node* const head, int data) {
    Node* current = head;
    if (current == nullptr) {
        // Corner case - LL is empty
        Node::printSLL(current);
        return current;
    } else if (current->next == nullptr) {
        // Corner case - LL has only 1 node
        cout << "The deleted node: " << current->data << endl;
        delete current;
        current = nullptr;
        Node::printSLL(current);
        return current;
    } else if (current->data == data) {
        // Corner case - LL has at least 2 nodes but the 1st node to be deleted
        Node* pop = current;
        current = current->next;
        cout << "The deleted node: " << pop->data << endl;
        delete pop;
        Node::printSLL(current);
        return current;
    } else if (current->next->data == data) {
        // Corner case - LL has at least 2 nodes but the 2nd node to be deleted
        Node* pop = current->next;
        current->next = pop->next;
        cout << "The deleted node: " << pop->data << endl;
        delete pop;
        Node::printSLL(current);
        return current;
    } else {
        while ((current->next)->data != data) {
            current = current->next;
        }
        Node* pop = current->next;
        current->next = pop->next;
        cout << "The deleted node: " << pop->data << endl;
        delete pop;
        Node::printSLL(head);
        return head;
    }
}

int main() {
    int arr1[] = {10,20,30,40,50}; int s1 = sizeof(arr1)/sizeof(int);
    Node* head1 = Node::buildSLLfromArray(arr1, s1);
    Node* head2 = deleteTargetNode(head1, 30);
    return 0;
}