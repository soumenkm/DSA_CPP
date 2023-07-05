/*

// Linking process of 2 C++ files
g++ -std=c++11 -c file1.cpp // Creates the object file file1.o (compiled version)
g++ -std=c++11 -c file2.cpp // Creates teh object file file2.o (compiled version)
g++ -std=c++11 file1.o file2.o // Creates the linked file a.out (linked version)
./a.out // Execute the linked file


In C++, header files are often included in multiple source files.
When a header file is included, the code within it is copied into the source file.
This copying process can lead to problems if the same header file is included
multiple times in the same source file or across different source files.

To prevent these problems, include guards are used. Include guards are preprocessor
directives that ensure the code within the header file is only processed once, even
if it is included multiple times. They prevent redefinition errors and improve
compilation efficiency.

Here's a breakdown of the steps involved:

#ifndef NODE_H: This line checks if the macro NODE_H is not defined. If it's not defined,
it means this is the first time the header file Node.h is being included.
#define NODE_H: This line defines the macro NODE_H. By defining it, we mark that the header
file is being included, and subsequent inclusions will be skipped. The actual content of
the header file, including the class definition, function declarations, and other code,
follows after the include guard.
#endif: This line marks the end of the include guard. It closes the conditional
block started by #ifndef. It ensures that the code after the include guard is processed
only once. The purpose of the include guard is to ensure that the header file contents
are included only once, avoiding duplication and potential errors. It acts as a safeguard
to prevent redefinition of code and allows for the proper compilation and linking of the
program.

*/

#ifndef NODE_H
#define NODE_H

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Node {
    public:
        int data{0};
        Node* next{nullptr};

        // Constructors
        Node() = default;
        Node(const int _data):
            data{_data},
            next{nullptr} {}
        Node(Node* const _next):
            data{0},
            next{_next} {}
        Node(const int _data, Node* const _next):
            data{_data},
            next{_next} {}
        
        // Copy constructor
        Node(const Node& other):
            data{other.data},
            next{other.next} {}

        static void printSLL(const Node* const head) {
            const Node* current = head;
            while (current != nullptr) {
                cout << current->data << " --> ";
                current = current->next;
            }
            cout << "nullptr" << endl;
        }

        static int len(const Node* const head) {
            const Node* current = head;
            int length{0};
            while (current != nullptr) {
                current = current->next;
                length++;
            }
            cout << "Length of the linked list: " << length << endl;
            return length;
        }

        static Node* buildSLL() {
            cout << "Enter integers seperated by space. " << 
                "To stop type any character and hit enter" << endl;
            int data{0};
            cin >> data;
            
            Node* const head = new Node(data);
            Node* prev = head;

            // cin >> data condition will be false if we provide float or string
            // or character instead of int as data is int type. It will also be false
            // when the EOF or CTRL+D is reached. As long as the valid int input is
            // provided it will be true (use getline for an alternative option)

            while (cin >> data) {
                Node* current = new Node(data);
                prev->next = current;
                prev = current;
            }
            cin.clear(); // To clear the error codes from the input buffer

            // numeric_limits<type> is a class template which works for any type
            // We access the static member function max() using :: operator

            // long int_max_limit = std::numeric_limits<int>::max();
            long stream_max_limit = std::numeric_limits<std::streamsize>::max();
            
            // In the cin.ignore(num, '\n') statement, it means to ignore characters in the
            // input stream until either 'num' of characters have been ignored or a newline
            // character ('\n') is encountered, whichever happens first

            cin.ignore(stream_max_limit,'\n');
            Node::printSLL(head);
            // Node::len(head);
            return head;
        } 

        static Node* buildSLLfromArray(const int* const arr, const int size) {
            if (size == 0) {
                Node::printSLL(nullptr);
                // Node::len(nullptr);
                return nullptr;
            }
            else {
                Node* const head = new Node(arr[0]);
                Node* prev = head;
                for (int i = 1; i < size; i++) {
                    Node* current = new Node(arr[i]);
                    prev->next = current;
                    prev = current;
                }
                Node::printSLL(head);
                // Node::len(head);
                return head;
            }
        }

        static void freeSLL(Node* const head) {
            Node* current = head;
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            cout << "Successfully deleted the linked list" << endl;
        }
        
};

#endif