#include <iostream>
#include <vector>
#include <string>

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

    BSTNode* getParentNode(int elem) {
        // to be implemented
    }

    BSTNode* deleteNode(const int elem, BSTNode* const parent = nullptr) {
        static int numCall {0};
        numCall++;
        BSTNode* root = this;
        if (root == nullptr) {
            return nullptr;
        } else if (root->left == nullptr && root->right == nullptr && root->data == elem) {
            // The leaf node is deleted
            BSTNode* temp = root;
            delete temp;
            if (elem <= parent->data) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            
        } else if (root->left == nullptr && root->data == elem) {
            // Only the right child exists
            if (parent == nullptr) {
                BSTNode* temp = root->right;
                delete root;
                return temp;
            }
            if (elem <= parent->data) {
                parent->left = root->right;
            } else {
                parent->right = root->right;
            }
            delete root;
        } else if (root->right == nullptr && root->data == elem) {
            // Only the left child exists
            if (parent == nullptr) {
                BSTNode* temp = root->left;
                delete root;
                return temp;
            }
            if (elem <= parent->data) {
                parent->left = root->left;
            } else {
                parent->right = root->left;
            }
            delete root;
        } else if (root->data == elem) {
            // Both the child exists
            BSTNode* pred = root->left->search(root->left->getExtreme("max"));
            int temp = pred->data;
            pred->data = root->data;
            root->data = temp;
            pred->deleteNode(elem, root); // bug - parent
        } else if (elem <= root->data) {
            root->left->deleteNode(elem, root);
        } else if (elem > root->data) {
            root->right->deleteNode(elem, root);
        } else {
            throw runtime_error("Something went wrong!");
        }
        return root;
    } 

};


int main() {
    vector<int> elemArray {6,3,1,-3,2,5,4,9,7,11,12};
    BSTNode* root = BSTNode::buildBST(elemArray);

    root->print("in");
    root->print("pre");

    // root = root->deleteNode(6);
    // root->print("in");

    // BSTNode* node = root->getParentNode(3);
    // node? cout << node->data << endl : cout << "parent is NULL" << endl;

    return 0;
}