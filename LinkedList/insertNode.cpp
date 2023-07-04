#include <iostream>

using std::cout;
using std::cin;
using std::getline;
using std::endl;

class Node {
    public:
        int data{0};
        Node* next{nullptr};

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
            cin.clear();

            // numeric_limits<type> is a class template which works for any type
            // We access the static member function max() using :: operator

            long int_max_limit = std::numeric_limits<int>::max();
            long stream_max_limit = std::numeric_limits<std::streamsize>::max();
            // cout << int_max_limit << " " << stream_max_limit << endl;
            
            // In the cin.ignore(num, '\n') statement, it means to ignore characters in the
            // input stream until either 'num' of characters have been ignored or a newline
            // character ('\n') is encountered, whichever happens first

            cin.ignore(stream_max_limit,'\n');
            Node::printSLL(head);
            Node::len(head);
            return head;
        } 

        // static Node* buildSLLfromArray(const int* const arr, const int num) {

        // }
};


int main() {
    cout << "Hello World!" << endl;
    Node* head1 = Node::buildSLL();
    Node* head2 = Node::buildSLL();
    Node* head3 = nullptr;
    return 0;
}