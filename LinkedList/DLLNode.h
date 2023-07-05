#ifndef DLLNODE_H
#define DLLNODE_H

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class DLLNode {
    public:
        int data{0};
        DLLNode* prev{nullptr};
        DLLNode* next{nullptr};

        DLLNode(int _data):
            data{_data},
            prev{nullptr},
            next{nullptr} {}
        DLLNode(int _data, DLLNode* _prev, DLLNode* _next):
            data{_data},
            prev{_prev},
            next{_next} {}

        static void printDLL(DLLNode* const head) {
            if (head == nullptr) {
                cout << "nullptr" << endl;
            } else {
                DLLNode* current = head;
                cout << "nullptr <--> ";
                while (current != nullptr) {
                    cout << current->data << " <--> ";
                    current = current->next;
                }
                cout << "nullptr" << endl;
            }
        }

        static DLLNode* buildDLLfromArray(int* const arr, const int size) {
            if (size == 0) {
                DLLNode* head = nullptr;
                DLLNode::printDLL(head);
                return head;
            } else {
                DLLNode* const head = new DLLNode(arr[0]);
                DLLNode* backward = head;
                for (int i = 1; i < size; i++) {
                    DLLNode* current = new DLLNode(arr[i]);
                    backward->next = current;
                    current->prev = backward;
                    backward = current;
                    current = current->next;
                }
                DLLNode::printDLL(head);
                return head;
            }
        }

};

#endif