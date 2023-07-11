#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <string>
#include <tuple>

using std::cin;
using std::cout;
using std::endl;

class TreeNode {
public:
    int data{0};
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};

public:
    TreeNode() = default;
    
    TreeNode(int _data, TreeNode* _left = nullptr, TreeNode* _right = nullptr) {
        this->data = _data;
        this->left = _left;
        this->right = _right;
    }
    
    TreeNode(TreeNode* other) {
        this->data = other->data;
        this->left = other->left;
        this->right = other->right;
    }
    
    static TreeNode* buildBT(char type = 'r') {
        TreeNode* root{nullptr};
        if (type == 'p') {
            /*
            
                   10
             /            \
           20             30
          /  \           /   \
        40    50       60     70
      /  \   /  \     / \     / \
    80   90  100 110 120 130 140 150

            */
            root = new TreeNode(10);

            root->left = new TreeNode(20);
            root->right = new TreeNode(30);

            root->left->left = new TreeNode(40);
            root->left->right = new TreeNode(50);
            root->right->left = new TreeNode(60);
            root->right->right = new TreeNode(70);

            root->left->left->left = new TreeNode(80);
            root->left->left->right = new TreeNode(90);
            root->left->right->left = new TreeNode(100);
            root->left->right->right = new TreeNode(110);
            root->right->left->left = new TreeNode(120);
            root->right->left->right = new TreeNode(130);
            root->right->right->left = new TreeNode(140);
            root->right->right->right = new TreeNode(150);
        } else if (type == 'c') {
            /*
            
                   10
             /            \
           20             30
          /  \           /   \
        40    50       60     70
      /  \   /  \     /
    80   90  100 110 120

            
            */
            root = new TreeNode(10);

            root->left = new TreeNode(20);
            root->right = new TreeNode(30);

            root->left->left = new TreeNode(40);
            root->left->right = new TreeNode(50);
            root->right->left = new TreeNode(60);
            root->right->right = new TreeNode(70);

            root->left->left->left = new TreeNode(80);
            root->left->left->right = new TreeNode(90);
            root->left->right->left = new TreeNode(100);
            root->left->right->right = new TreeNode(110);
            root->right->left->left = new TreeNode(120);
        } else if (type == 'f') {
            /*
            
               10
             /     \
           20       30
                    /   \
                  60     70
                        /   \
                        140  150


            */
            root = new TreeNode(10);

            root->left = new TreeNode(20);
            root->right = new TreeNode(30);

            root->right->left = new TreeNode(60);
            root->right->right = new TreeNode(70);

            root->right->right->left = new TreeNode(140);
            root->right->right->right = new TreeNode(150);
        } else {
            /*

                10
             /     \
           20       30
          /         /   \
        40        60     70
         \       / \       \
         90   120  130      150
         /
         160

            */
            root = new TreeNode(10);

            root->left = new TreeNode(20);
            root->right = new TreeNode(30);

            root->left->left = new TreeNode(40);
            root->right->left = new TreeNode(60);
            root->right->right = new TreeNode(70);

            root->left->left->right = new TreeNode(90);
            root->right->left->left = new TreeNode(120);
            root->right->left->right = new TreeNode(130);
            root->right->right->right = new TreeNode(150);

            root->left->left->right->left = new TreeNode(160);
        }
        return root;
    }
    
    int numberOfNodes() const {
        const TreeNode* const root = this;
        if (root == nullptr) {
            /*
            Nodes which are actually NULL (maybe one left child is NULL or 
            the right child is NULL for the parent node of this current root node)
                    10
                    /  \
                NULL  20     -> When current root is NULL then it will be an empty BT
                        / \ 
                    NULL NULL
            So here when root is acually NULL, it should return 0 as it is not a node 
            NULL represents the absense of a node.
            */
            return 0;
        } else {
            int s1 = root->left->numberOfNodes();
            int s2 = root->right->numberOfNodes();
            int s = s1 + s2 + 1;
            return s;
        }
    }
    
    int numberOfLeafs() const {
        const TreeNode* const root = this;
        if (root == nullptr) {
            return 0; // Empty BT or any 1 child of root's parent is missing so not a leaf node
        } else if (root->left == nullptr && root->right == nullptr) {
            return 1;
        } else {
            int l1 = root->left->numberOfLeafs();
            int l2 = root->right->numberOfLeafs();
            int l = l1 + l2;
            return l;
        }
    }

    int numberOfInts() const {
        const TreeNode* const root = this;
        if (root == nullptr) {
            return 0; // Empty BT or any 1 child of root's parent is missing so not a leaf node
        } else if (root->left == nullptr && root->right == nullptr) {
            return 0;
        } else {
            int l1 = root->left->numberOfInts();
            int l2 = root->right->numberOfInts();
            int l = l1 + l2 + 1;
            return l;
        }
    }

    int heightOfNode() {
        const TreeNode* const root = this;
        if (root == nullptr) {
            return -1;
        } else {
            int h1 = root->left->heightOfNode();
            int h2 = root->right->heightOfNode();
            int max = (h1>h2) ? (h1) : (h2);
            int h = max + 1;
            return h;
        }
    }

    std::tuple<int, TreeNode*> findDeepestNode() {
        TreeNode* const root = this;
        if (root == nullptr) {
            return std::tuple {-1, nullptr};
        } else if (root->left == nullptr && root->right == nullptr) {
            return std::tuple {0, root};
        } else {
            std::tuple<int, TreeNode*> lst = root->left->findDeepestNode();
            std::tuple<int, TreeNode*> rst = root->right->findDeepestNode();

            int h1 = std::get<0>(lst);
            TreeNode* n1 = std::get<1>(lst);
            int h2 = std::get<0>(rst);
            TreeNode* n2 = std::get<1>(rst);

            if (h1 >= h2) {
                return std::tuple(h1+1, n1);
            } else {
                return std::tuple(h2+1, n2);
            }
        }
    }

    int depthOfNode(TreeNode* target) const {
        const TreeNode* const root = this;
        if (target == nullptr) {
            throw std::runtime_error("target cannot be NULL");
        } else if (root == nullptr) {
            return -1; // target is not found in the LST/RST rooted at parent of current root
        } else if (root == target) {
            return 0; // target is found in the LST/RST rooted at parent of current root
        } else {
            int d1 = root->left->depthOfNode(target);
            int d2 = root->right->depthOfNode(target);

            if (d1 == -1 && d2 == -1) {
                return -1; // target is not in the tree
            } else if (d1 == -1 && d2 != -1) {
                return d2 + 1; // +1 for root to the RST
            } else if (d1 != -1 && d2 == -1) {
                return d1 + 1; // +1 for root to the LST
            } else {
                throw std::runtime_error("Cycle detected, target cannot be present in both ST");
            }
        }
    }

    std::string preOrder() const {
        const TreeNode* const root = this;
        if (root == nullptr) {
            return std::string {""};
        } else {
            // cout << root->data << " ";
            std::string lst = root->left->preOrder();
            std::string rst = root->right->preOrder();
            std::string res = std::to_string(root->data) + " " + lst + rst;
            return res;
        }
    }

    std::string postOrder() const {
        const TreeNode* const root = this;
        if (root == nullptr) {
            return std::string {""};
        } else {
            std::string lst = root->left->postOrder();
            std::string rst = root->right->postOrder();
            // cout << root->data << " ";
            std::string res = lst + rst + std::to_string(root->data) + " ";
            return res;
        }
    }

    std::string inOrder() const {
        const TreeNode* const root = this;
        if (root == nullptr) {
            return std::string {""};
        } else {
            std::string lst = root->left->inOrder();
            // cout << root->data << " ";
            std::string rst = root->right->inOrder();
            std::string res = lst + std::to_string(root->data) + " " + rst;
            return res;
        }
    }

    void deleteBT() {
        TreeNode* root = this;
        if (root == nullptr) {
            return;
        } else if (root->left == nullptr && root->right == nullptr) {
            delete root;
        } else {
            root->left->deleteBT();
            root->right->deleteBT();
            delete root;
            return;
        }
    }

    static TreeNode* buildBTfromInAndPre(const int* in, int inSize, const int* pre, int preSize) {
        // Assumption: Duplicate elements do not exist in traversal
        static int callNo = 0;
        
        if (inSize <= 0) {
            return nullptr;
        } else {
            // Find the root first
            TreeNode* root {nullptr};
            if (callNo == 0) {
                // First call - root is first element of preorder
                root = new TreeNode {pre[0]};
                callNo++;
            } else {
                // Any other call - root need to be searched in preorder 
                // The first common element in both pre and inorder will be root
                int rootData {-1};
                for (int i = 0; i < preSize; i++) {
                    bool br {false};
                    for (int j = 0; j < inSize; j++) {
                        if (pre[i] == in[j]) {
                            rootData = pre[i];
                            br = true;
                            break;
                        }
                    }
                    if (br) {
                        break;
                    }
                }
                root = new TreeNode(rootData);
                callNo++;
            }

            // Divide the preOrder array
            pre++;
            preSize--;

            // Divide the inOrder array
            int in1Size {0};
            int in2Size {0};
            for (int i = 0; i < inSize; i++) {
                if (in[i] == root->data) {
                    in1Size = i;
                    break;
                }
            }
            in2Size = inSize - 1 - in1Size;

            // Conquer recursively
            TreeNode* lst = buildBTfromInAndPre(in, in1Size, pre, preSize);
            TreeNode* rst = buildBTfromInAndPre(in+in1Size+1, in2Size, pre, preSize);

            // Combine
            root->left = lst;
            root->right = rst;
            return root;
        }
    }

    static void printArray(int* array, int size) {
        for (int i = 0; i < size; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    static void deleteArray(int* array) {
        delete [] array;
    }

    static std::tuple<int*,int> splitStringToArray(std::string str, char delim = ' ') {

        class Node {
        public:
            int data {-1};
            Node* next {nullptr};
            Node(int _data = -1, Node* _next = nullptr) {
                this->data = _data;
                this->next = _next;
            }
            static void printLL(Node* head) {
                while (head != nullptr) {
                    cout << head->data << " --> ";
                    head = head->next;
                }
                cout << "NULL" << endl;
            }
            static int len(Node* head) {
                int len {0};
                while (head != nullptr) {
                    len++;
                    head = head->next;
                }
                return len;
            }
        };

        Node* head = new Node{};
        Node* current = head;
        
        int sizeStr = str.length();
        if (str[sizeStr-1] != delim) {
            std::string end {""};
            end += delim;
            str = str + end;
            sizeStr++;
        }

        std::string num {""};
        for (int i = 0; i < sizeStr; i++) {
            char c = str[i];
            if (c != delim) {
                num = num + std::string(1,c);
            } else {
                int elem = std::stoi(num);
                current->next = new Node {elem};
                current = current->next;
                num = std::string {""};
            }       
        }
        head = head->next;
        current = head;

        int lenArray = Node::len(head);
        int* array = new int[lenArray] ();
        for (int i = 0; i < lenArray; i++) {
            array[i] = current->data;
            current = current->next;
        }
        
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        return std::tuple {array, lenArray};
    }

};

#endif
