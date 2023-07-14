#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <queue>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::runtime_error;

class BSTNode {
public:
    int data {-1};
    BSTNode* left {nullptr};
    BSTNode* right {nullptr};
public:
    BSTNode(int _data = -1, BSTNode* _left = nullptr, BSTNode* _right = nullptr):
        data {_data}, left {_left}, right {_right} {}
    
    BSTNode* deleteBST() {
        BSTNode* root = this;
        if (root == nullptr) {
            return nullptr;
        } else if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        } else {
            root->left->deleteBST();
            root->right->deleteBST();
            delete root;
            return nullptr;
        }
    }

    static void printVector(vector<int>* vec) {
        for (int i: *vec) cout << i << " ";
        cout << endl;
    }

    static void printArray(int* arr, int size) {
        for (int i = 0; i < size; i++) cout << arr[i] << " ";
        cout << endl;
    }

    void print(const string order = "pre" ,const int _num = 0) {
        BSTNode* root = this;
        if (root == nullptr) {
            return;
        } else {
            if (order == "pre") {
                cout << root->data << " ";
                root->left->print("pre", 1);
                root->right->print("pre" ,1);
            } else if (order == "post") {
                root->left->print("post", 1);
                root->right->print("post" ,1);
                cout << root->data << " ";                
            } else if (order == "in") {
                root->left->print("in", 1);
                cout << root->data << " ";
                root->right->print("in" ,1);
            } else {
                throw runtime_error("Invalid order!");
            }
            if (_num == 0) {
                cout << endl;
            }
        }
    }

    int size() {
        BSTNode* root = this;
        if (root == nullptr) {
            return 0;
        } else {
            return this->left->size() + this->right->size() + 1;
        }
    }

    void insertNode(const int elem) {
        BSTNode* root = this;
        if (root == nullptr) {
            throw runtime_error("Cannot insert a node in empty BST!");
        } else if (root->left == nullptr && elem <= root->data) {
            BSTNode* node = new BSTNode {elem};
            root->left = node;
        } else if (root->right == nullptr && elem > root->data) {
            BSTNode* node = new BSTNode {elem};
            root->right = node;
        } else if (elem <= root->data) {
            root->left->insertNode(elem);
        } else {
            root->right->insertNode(elem);
        }
    }

    static BSTNode* buildBST(const vector<int>& array) {
        if (array.empty()) {
            return nullptr;
        } else {
            BSTNode* root = new BSTNode {array[0]};
            int size = array.size();
            for (int i = 1; i < size; i++) {
                root->insertNode(array[i]);
            }
            return root;
        }
    }

    int getExtreme(const string type) {
        BSTNode* root = this;
        if (root == nullptr) {
            return -1;
        } else if (root->left == nullptr && type == "min") {
            return root->data;
        } else if (root->right == nullptr && type == "max") {
            return root->data;
        } else if (type == "min") {
            return root->left->getExtreme(type);
        } else if (type == "max") {
            return root->right->getExtreme(type);
        } else {
            throw runtime_error("Invalid type!");
        }
    }

    vector<int>* getInOrder() {
        BSTNode* root = this;
        if (root == nullptr) {
            return new vector<int> {};
        } else if (root->left == nullptr && root->right == nullptr) {
            return new vector<int> {root->data};
        } else {
            vector<int>* leftArrPtr = root->left->getInOrder();
            leftArrPtr->push_back(root->data);
            vector<int>* rightArrPtr = root->right->getInOrder();

            leftArrPtr->insert(
                leftArrPtr->end(), rightArrPtr->begin(), rightArrPtr->end()
            );

            vector<int>* arrPtr = new vector<int> {*leftArrPtr};
            
            delete leftArrPtr;
            delete rightArrPtr;
            return arrPtr;
        }
    }

    int getKthExtreme(const int k, const string type) {
        // k starts with 0
        vector<int>* inArrPtr = this->getInOrder();
        int res {-1};
        int size = inArrPtr->size();
        if (type == "max") res = inArrPtr->at(k);
        else if (type == "min") res = inArrPtr->at(size-1-k);
        else throw runtime_error("Invalid type!");
        
        delete inArrPtr;
        return res;
    }

    int* getInOrderByArray() {
        BSTNode* root = this;
        if (root == nullptr) {
            // If the root is null then simply create an empty array
            return new int[0] {};
        } else if (root->left == nullptr && root->right == nullptr) {
            // If the root is leaf then simply create a single element array
            return new int[1] {root->data};
        } else {
            // Conquer the problem by calling left and right subtree recursively
            int* res1 = root->left->getInOrderByArray();
            int res1Size = root->left->size();
            int* res2 = root->right->getInOrderByArray();
            int res2Size = root->right->size();

            // Create the array in heap
            int* res = new int[res1Size+res2Size+1] {};
            
            // Store the left subtree
            int i = 0;
            int k1 = 0;
            while (k1 < res1Size) {
                res[i] = res1[k1];
                i++; k1++;
            }
            
            // Store the root node
            res[i] = root->data;
            i++;

            // Store the right subtree
            int k2 = 0;
            while (k2 < res2Size) {
                res[i] = res2[k2];
                i++; k2++;
            }

            // Delete the heap arrays
            delete [] res1;
            delete [] res2;

            return res;
        }
    }

    vector<int>* rangeSearch(const int min, const int max) {
        BSTNode* root = this;
        vector<int>* vec1 {nullptr};
        vector<int>* vec2 {nullptr};
        vector<int>* resVec {nullptr};

        if (root == nullptr) {
            return new vector<int> {};
        } else if (root->left == nullptr && root->right == nullptr) {
            if (root->data < min || root-> data > max) {
                return new vector<int> {};
            } else {
                return new vector<int> {root->data};
            }
        } else if (root->data < min) {
            // Suppose [4,6] and root is 2 so we have to go to right
            vec1 = new vector<int> {}; // root is out of range
            vec2 = root->right->rangeSearch(min, max);
        } else if (root->data > max) {
            // Suppose [4,6] and root is 8 so we have to go to left
            vec1 = root->left->rangeSearch(min, max);
            vec2 = new vector<int> {}; // root is out of range
        } else {
            // Suppose [4,6] and root is 5 so we have to go to both
            vec1 = root->left->rangeSearch(min, max);
            vec1->push_back(root->data); // root is in the range
            vec2 = root->right->rangeSearch(min, max);
        }

        // Merge all the vectors
        vec1->insert(vec1->end(), vec2->begin(), vec2->end());

        // Create the result vector
        resVec = new vector<int> {*vec1};

        // Delete the temporary vectors
        delete vec1;
        delete vec2;

        // Return the results
        return resVec;
    }

    BSTNode* search(const int elem) {
        BSTNode* root = this;
        if (root == nullptr) {
            // cout << "Search element " << elem << " is NOT found in BST" << endl;
            return nullptr;
        } else if (root->data == elem) {
            // cout << "Search element " << elem << " is found in BST" << endl;
            return root;
        } else if (elem <= root->data){
            return root->left->search(elem);
        } else if (elem > root->data) {
            return root->right->search(elem);
        } else {
            throw runtime_error("Something went wrong!");
        }
    }

    int getInOrderTerm(const char type, int elem) {
        BSTNode* root = this;
        // Not correct solution
        // return root->right->getExtreme("min");
        vector<int>* inArr = root->getInOrder();
        int size = inArr->size();
        int index {-1};
        for (int i = 0; i < size; i++) {
            if (inArr->at(i) == elem) {
                index = i;
                break;
            }
        }
        int p {-1};
        int s {-1};
        if (size <= 1) {
            p = -1;
            s = -1;
        } else if (index == 0) {
            p = -1;
            s = (*inArr)[index+1];
        } else if (index == size-1) {
            p = (*inArr)[index-1];
            s = -1;
        } else {
            p = (*inArr)[index-1];
            s = (*inArr)[index+1];
        }
        if (type == 'p') return p;
        else if (type == 's') return s;
        else throw runtime_error("Invalid type!");
    }

    std::map<BSTNode*, BSTNode*>* getParentMap() {
        BSTNode* root = this;
        static std::stack<BSTNode*> nodeStack {};
        if (root == nullptr) {
            // if root is null then we don't do anything as null parent doesn't make sense
            std::map<BSTNode*, BSTNode*>* res = new std::map<BSTNode*, BSTNode*> {};
            return res;
        } else if (root->left == nullptr && root->right == nullptr) {
            // if root is leaf then we peek at the stack top and it will be the parent
            std::map<BSTNode*, BSTNode*>* res = new std::map<BSTNode*, BSTNode*>
                                                {std::make_pair(root, nodeStack.top())};
            return res;
        } else {
            // Divide - first push the root to remember it later
            nodeStack.push(root);

            // Conquer - get the parent for lst and rst recursively
            std::map<BSTNode*, BSTNode*>* res1 = root->left->getParentMap();
            std::map<BSTNode*, BSTNode*>* res2 = root->right->getParentMap();
            
            // Combine - get the parent for root
            // merge the 2 maps
            res1->insert(res2->begin(),res2->end());
            
            // pop the top root node because at the time of division, it was pushed
            nodeStack.pop();

            // if the top is empty then nullptr will be parent of root else the current top
            // will be the parent of root
            if (nodeStack.empty()) {
                res1->insert(std::make_pair(root,nullptr));
            } else {
                BSTNode* p = nodeStack.top();
                res1->insert(std::make_pair(root,p));
            }

            // delete the individual maps and store the merged map only
            std::map<BSTNode*, BSTNode*>* res = new std::map<BSTNode*, BSTNode*> {*res1};
            delete res1;
            delete res2;

            return res;
        }
    }

    BSTNode* deleteNode(const int elem) {
        // Get the parents map and parent of current root
        BSTNode* root = this;
        static int c {0};
        c++;
        static BSTNode* retVal {nullptr};
        if (c == 1) {
            retVal = root;
        } 
        static std::map<BSTNode*, BSTNode*>* parentMap {root->getParentMap()};
        BSTNode* parent = (*parentMap)[root]; // parent for the current root

        if (root == nullptr) {
            // if the root is nullptr then do nothing and return the nullptr
            return nullptr;
        } else if (root->left == nullptr && root->right == nullptr && root->data == elem) {
            // if the root is leaf node then leaf node is deleted directly and return the
            // parent node of it
            BSTNode* temp = root;
            delete temp;
            if (parent != nullptr) {
                // if parent is not null then we set the 2 pointers of parent
                //  to null after deleting the leaf node and finally return original root node
                if (elem <= parent->data) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
                return retVal;
            } else {
                // if parent is null then the tree becomes empty so return null
                return nullptr;
            }
            
        } else if (root->left == nullptr && root->data == elem) {
            // Only the right child exists and this node to be deleted
            if (parent == nullptr) {
                // if the parent is null then we delete root and return its right child
                BSTNode* temp = root->right;
                delete root;
                return temp;
            } else {
                // if the parent is not null then connect parent to right child of root
                if (elem <= parent->data) {
                    // if the parent to root is left connected then we set the left 
                    // pointer of parent to root right child
                    parent->left = root->right;
                } else {
                    // if the parent to root is right connected then we set the right
                    // pointer of parent to root right child
                    parent->right = root->right;
                }
                // delete the root and return the original root
                delete root;
                return retVal;
            }

        } else if (root->right == nullptr && root->data == elem) {
            // Only the left child exists and this node to be deleted
            if (parent == nullptr) {
                // if the parent is null then we delete root and return its left child
                BSTNode* temp = root->left;
                delete root;
                return temp;
            } else {
                // if the parent is not null then connect parent to left child of root
                if (elem <= parent->data) {
                    // if the parent to root is left connected then we set the left 
                    // pointer of parent to root left child
                    parent->left = root->left;
                } else {
                    // if the parent to root is right connected then we set the right
                    // pointer of parent to root left child
                    parent->right = root->left;
                }
                // delete the root and return the original root
                delete root;
                return retVal;
            }

        } else if (root->data == elem) {
            // Both the child exists and this node to be deleted
            // first obtain the predecessor
            BSTNode* pred = root->left->search(root->left->getExtreme("max"));

            // record the pred data that will be later replace to root
            int temp = pred->data;
            
            // delete the pred node with pred data in it
            BSTNode* res = pred->deleteNode(pred->data); // send the pred data now, not elem
            
            // replace the root with the pred data
            root->data = temp;
            
            if (parent == nullptr) {
                return res; // return res if parent is null and new root will be res
            } else {
                return retVal; // if res is not null then original root will not change
            }

        } else if (elem <= root->data) {
            // check if the elem to be deleted is present in left subtree then 
            // recursively delete the node from left subtree
            BSTNode* res = root->left->deleteNode(elem);
            if (parent == nullptr) {
                return res; // return res if parent is null and new root will be res
            } else {
                return retVal; // if res is not null then original root will not change
            }
        } else if (elem > root->data) {
            // check if the elem to be deleted is present in right subtree then 
            // recursively delete the node from right subtree
            BSTNode* res = root->right->deleteNode(elem);
            if (parent == nullptr) {
                return res;
            } else {
                return retVal;
            }
        } else {
            // if the control enters here then some corner cases are not considered
            throw runtime_error("Something went wrong!");
        }
    } 

    vector<int>* levelOrder() {
        BSTNode* root = this;
        std::queue<BSTNode*> nodeQ {};
        nodeQ.push(root); // original root is pushed only one time
        vector<int> levelOrder {};
        
        // iterate through the queue until it is empty (front/root is null)
        while (root != nullptr) {
            // push root's childrens   
            if (root->left != nullptr) {
                nodeQ.push(root->left);
            }
            if (root->right != nullptr) {
                nodeQ.push(root->right);
            }

            // record the front in vector
            // cout << nodeQ.front()->data << " " << std::flush;
            levelOrder.push_back(nodeQ.front()->data); // print the front

            // delete the front node
            nodeQ.pop(); // dequeue the front element
            
            // automatically, after delete the pointer goes to next element
            root = nodeQ.front(); // update the root
        }
        
        // Create a vector in heap and return
        vector<int>* resPtr = new vector<int> {levelOrder};
        return resPtr;
    }

};

#endif