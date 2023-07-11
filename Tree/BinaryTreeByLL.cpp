#include <iostream>
#include <string>
#include <tuple>

using std::cin;
using std::cout;
using std::endl;

class BTnode {
public:
    int data{0};
    BTnode* left{nullptr};
    BTnode* right{nullptr};

public:
    BTnode() = default;
    BTnode(int _data, BTnode* _left = nullptr, BTnode* _right = nullptr) {
        this->data = _data;
        this->left = _left;
        this->right = _right;
    }
    BTnode(BTnode* other) {
        this->data = other->data;
        this->left = other->left;
        this->right = other->right;
    }
    static BTnode* buildBT(char type = 'r') {
        BTnode* root{nullptr};
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
            root = new BTnode(10);

            root->left = new BTnode(20);
            root->right = new BTnode(30);

            root->left->left = new BTnode(40);
            root->left->right = new BTnode(50);
            root->right->left = new BTnode(60);
            root->right->right = new BTnode(70);

            root->left->left->left = new BTnode(80);
            root->left->left->right = new BTnode(90);
            root->left->right->left = new BTnode(100);
            root->left->right->right = new BTnode(110);
            root->right->left->left = new BTnode(120);
            root->right->left->right = new BTnode(130);
            root->right->right->left = new BTnode(140);
            root->right->right->right = new BTnode(150);
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
            root = new BTnode(10);

            root->left = new BTnode(20);
            root->right = new BTnode(30);

            root->left->left = new BTnode(40);
            root->left->right = new BTnode(50);
            root->right->left = new BTnode(60);
            root->right->right = new BTnode(70);

            root->left->left->left = new BTnode(80);
            root->left->left->right = new BTnode(90);
            root->left->right->left = new BTnode(100);
            root->left->right->right = new BTnode(110);
            root->right->left->left = new BTnode(120);
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
            root = new BTnode(10);

            root->left = new BTnode(20);
            root->right = new BTnode(30);

            root->right->left = new BTnode(60);
            root->right->right = new BTnode(70);

            root->right->right->left = new BTnode(140);
            root->right->right->right = new BTnode(150);
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
            root = new BTnode(10);

            root->left = new BTnode(20);
            root->right = new BTnode(30);

            root->left->left = new BTnode(40);
            root->right->left = new BTnode(60);
            root->right->right = new BTnode(70);

            root->left->left->right = new BTnode(90);
            root->right->left->left = new BTnode(120);
            root->right->left->right = new BTnode(130);
            root->right->right->right = new BTnode(150);

            root->left->left->right->left = new BTnode(160);
        }
        return root;
    }
};

int numberOfNodes(BTnode* root) {
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
        int s1 = numberOfNodes(root->left);
        int s2 = numberOfNodes(root->right);
        int s = s1 + s2 + 1;
        return s;
    }
}

int numberOfLeafs(BTnode* root) {
    if (root == nullptr) {
        return 0; // Empty BT or any 1 child of root's parent is missing so not a leaf node
    } else if (root->left == nullptr && root->right == nullptr) {
        return 1;
    } else {
        int l1 = numberOfLeafs(root->left);
        int l2 = numberOfLeafs(root->right);
        int l = l1 + l2;
        return l;
    }
}

int numberOfInts(BTnode* root) {
    if (root == nullptr) {
        return 0; // Empty BT or any 1 child of root's parent is missing so not a leaf node
    } else if (root->left == nullptr && root->right == nullptr) {
        return 0;
    } else {
        int l1 = numberOfInts(root->left);
        int l2 = numberOfInts(root->right);
        int l = l1 + l2 + 1;
        return l;
    }
}

int heightOfNode(BTnode* root) {
    if (root == nullptr) {
        return -1;
    } else {
        int h1 = heightOfNode(root->left);
        int h2 = heightOfNode(root->right);
        int max = (h1>h2) ? (h1) : (h2);
        int h = max + 1;
        return h;
    }
}

std::tuple<int, BTnode*> findDeepestNode(BTnode* root) {
    if (root == nullptr) {
        return std::tuple {-1, nullptr};
    } else if (root->left == nullptr && root->right == nullptr) {
        return std::tuple {0, root};
    } else {
        std::tuple<int, BTnode*> lst = findDeepestNode(root->left);
        std::tuple<int, BTnode*> rst = findDeepestNode(root->right);

        int h1 = std::get<0>(lst);
        BTnode* n1 = std::get<1>(lst);
        int h2 = std::get<0>(rst);
        BTnode* n2 = std::get<1>(rst);

        if (h1 >= h2) {
            return std::tuple(h1+1, n1);
        } else {
            return std::tuple(h2+1, n2);
        }
    }
}

int depthOfNode(BTnode* root, BTnode* target) {
    if (target == nullptr) {
        throw std::runtime_error("target cannot be NULL");
    } else if (root == nullptr) {
        return -1; // target is not found in the LST/RST rooted at parent of current root
    } else if (root == target) {
        return 0; // target is found in the LST/RST rooted at parent of current root
    } else {
        int d1 = depthOfNode(root->left, target);
        int d2 = depthOfNode(root->right, target);

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

std::string preOrder(BTnode* root) {
    if (root == nullptr) {
        return std::string {""};
    } else {
        // cout << root->data << " ";
        std::string lst = preOrder(root->left);
        std::string rst = preOrder(root->right);
        std::string res = std::to_string(root->data) + " " + lst + rst;
        return res;
    }
}

std::string postOrder(BTnode* root) {
    if (root == nullptr) {
        return std::string {""};
    } else {
        std::string lst = postOrder(root->left);
        std::string rst = postOrder(root->right);
        // cout << root->data << " ";
        std::string res = lst + rst + std::to_string(root->data) + " ";
        return res;
    }
}

std::string inOrder(BTnode* root) {
    if (root == nullptr) {
        return std::string {""};
    } else {
        std::string lst = inOrder(root->left);
        // cout << root->data << " ";
        std::string rst = inOrder(root->right);
        std::string res = lst + std::to_string(root->data) + " " + rst;
        return res;
    }
}

int main() {
    BTnode* root1 = BTnode::buildBT('r');
    std::string res1 = preOrder(root1);
    std::string res2 = postOrder(root1);
    std::string res3 = inOrder(root1);
    cout << "Preorder traversal of the tree: \n" << res1 << endl;
    cout << "Postorder traversal of the tree: \n" << res2 << endl;
    cout << "Inorder traversal of the tree: \n" << res3 << endl;
    return 0;
}