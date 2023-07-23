#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <stack>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::tuple;
using std::stack;
using std::string;

class Node {
public:
    int data {0};
    Node* next {nullptr};

public:
    explicit Node(const int _data = 0, Node* const _next = nullptr) {
        this->data = _data;
        this->next = _next;
    }
    ~Node() {
        // It only deletes the node, it does not delete the whole list
        // to delete whole list, call deleteLL method
        // do not write 'delete this' as it will again call ~Node so it will lead
        // to infinite recursion hence, do not write any code in destructor
        // delete this; 
    }
    void deleteLL() {
        Node* head = this;
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    static Node* buildLL(const int* const arr, const int size) {
        Node* head = new Node {};
        Node* current = head;
        for (int i = 0; i < size; i++) {
            Node* node = new Node {arr[i]};
            current->next = node;
            current = node;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    void printLL() {
        Node* head = this;
        while (head != nullptr) {
            cout << head->data << " --> ";
            head = head->next;
        }
        cout << "NULL" << endl;
    }

    Node* pushFront(const int elem) {
        Node* head = this;
        Node* node = new Node {elem, head};
        return node;
    }

    Node* popFront() {
        Node* head = this;
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    Node* popNode(const int elem) {
        Node* head = this;
        Node* headOrg = head;
        if (headOrg == nullptr) {
            return nullptr;
        } else if (headOrg->data == elem) {
            Node* temp = headOrg;
            headOrg = headOrg->next;
            delete temp;
            return headOrg;
        }
        else {
            while (head->next != nullptr) {
                if (head->next->data == elem) {
                    Node* temp = head->next;
                    head->next = temp->next;
                    delete temp;
                    break;
                }
                head = head->next;
            }
            return headOrg;
        }
    }

};

class Matrix {
public:
    int** array {nullptr};
    int row {0};
    int col {0};

public:
    explicit Matrix(const std::string& fileName) {
        // read the matrix from files
        std::ifstream fileObj {fileName};
        if (!fileObj) {
            throw std::runtime_error("Unable to open file!");
        }

        // read the 1st line as it contains the dimension
        fileObj >> this->row >> this->col;

        // read from 2nd line onwards for data
        this->array = new int* [this->row] {};
        for (int i = 0; i < this->row; i++) {
            this->array[i] = new int [this->col] {};
            for (int j = 0; j < this->col; j++) {
                fileObj >> this->array[i][j];
            }
        }
    }

    ~Matrix() {
        for (int i = 0; i < this->row; i++) {
            delete [] this->array[i];
        }
        delete [] this->array;
    }

    void printRow(const int index) const {
        for (int j = 0; j < this->col; j++) {
            cout << this->array[index][j] << " ";
        }
        cout << endl;
    }

    void printMatrix() const {
        for (int i = 0; i < this->row; i++) {
            this->printRow(i);
        }
    }
};

class GraphMatrix {
private:
    int** vertexArray {nullptr};
    int vertexSize {0};

public:
    explicit GraphMatrix(const Matrix* const matrix) {
        this->vertexSize = matrix->row;
        this->vertexArray = new int* [this->vertexSize] {};
        for (int i = 0; i < this->vertexSize; i++) {
            this->vertexArray[i] = new int [this->vertexSize] {};
            for (int j = 0; j < this->vertexSize; j++) {
                this->vertexArray[i][j] = matrix->array[i][j];
            }
        }
    }
    
    ~GraphMatrix() {
        for (int i = 0; i < this->vertexSize; i++) {
            delete [] this->vertexArray[i];
        }
        delete [] this->vertexArray;
    }

    void printGraph() const {
        for (int i = 0; i < this->vertexSize; i++) {
            cout << "Vertex " << i << ": --> ";
            for (int j = 0; j < this->vertexSize; j++) {
                if (this->vertexArray[i][j] == 1) {
                    cout << j << " --> ";
                }
            }
            cout << "END" << endl;
        }
    }

    int getDegree(const int vertexIndex) const {
        // for directed graph, it is out degree only
        int deg {0};
        for (int i = 0; i < this->vertexSize; i++) {
            deg = deg + this->vertexArray[vertexIndex][i];
        }
        return deg;
    }

    int getSumDegree() const {
        int sum {0};
        for (int i = 0; i < this->vertexSize; i++) {
            sum = sum + this->getDegree(i);
        }
        return sum;
    }

    int getEdgeSize(const char type) const {
        if (type == 'd') {
            return this->getSumDegree();
        } else if (type == 'u') {
            return (this->getSumDegree())/2;
        } else {
            throw std::runtime_error("Invalid type!");
        }
    }

    bool isEdge(const int srcIndex, const int dstIndex) const {
        bool res {false};
        if (this->vertexArray[srcIndex][dstIndex] == 1) {
            res = true;
        }
        return res;
    }

};

class GraphList {
public:
    Node** vertexArray {nullptr};
    int vertexSize {0};

public:
    explicit GraphList(const Matrix* const matrix) {
        this->vertexSize = matrix->row;
        this->vertexArray = new Node* [this->vertexSize] {};
        for (int i = 0; i < this->vertexSize; i++) {
            Node* adjList {nullptr}; // initially empty
            for (int j = 0; j < this->vertexSize; j++) {
                if (matrix->array[i][j] == 1) {
                    adjList = adjList->pushFront(j);
                }
            }
            this->vertexArray[i] = adjList;
        }
    }

    ~GraphList() {
        for (int i = 0; i < this->vertexSize; i++) {
            this->vertexArray[i]->deleteLL();
        }
        delete [] this->vertexArray;
    }

    void printGraph() const {
        for (int i = 0; i < this->vertexSize; i++) {
            cout << "Vertex " << i << ": --> ";
            this->vertexArray[i]->printLL();
        }
    }

    int getDegree(const int vertexIndex) const {
        // for directed graph, it is out degree only
        int deg {0};
        Node* head = this->vertexArray[vertexIndex];
        while (head != nullptr) {
            deg++;
            head = head->next;
        }
        return deg;
    }

    int getSumDegree() const {
        int sum {0};
        for (int i = 0; i < this->vertexSize; i++) {
            sum = sum + this->getDegree(i);
        }
        return sum;
    }

    int getEdgeSize(const char type) const {
        if (type == 'd') {
            return this->getSumDegree();
        } else if (type == 'u') {
            return (this->getSumDegree())/2;
        } else {
            throw std::runtime_error("Invalid type!");
        }
    }

    bool isEdge(const int srcIndex, const int dstIndex) const {
        Node* head = this->vertexArray[srcIndex];
        bool res {false};
        while (head != nullptr) {
            if (head->data == dstIndex) {
                res = true;
                break;
            }
            head = head->next;
        }
        return res;
    }

    void dfs(const int index, bool* const visitedArray, int n = 0) {
        visitedArray[index] = true;
        // set up the base case
        if (this->vertexArray[index] == nullptr) {
            cout << index << " --> " << std::flush;
        } else {
            // divide the problem in all the adjacents
            Node* head = this->vertexArray[index];
            cout << index << " --> " << std::flush; // for preorder first print the node
            while (head != nullptr) {
                if (!visitedArray[head->data]) {
                    dfs(head->data, visitedArray, 1); // if not visited then conquer it recursively
                }
                head = head->next;
            }
        }
        if (n == 0) {
            cout << "END" << endl;
        }
    }

    void DFSGraph() {
        bool* visitedArray = new bool [this->vertexSize] {};
        for (int i = 0; i < this->vertexSize; i++) {
            visitedArray[i] = false;
        }
        for (int i = 0; i < this->vertexSize; i++) {
            if (!(visitedArray[i])) {
                cout << "DFS(" << i << "): " << std::flush;
                this->dfs(i, visitedArray);
            }
        }
        delete [] visitedArray;
    }

    vector<int*> getTraverseTime(const int startVertex, int n = 0) {
        // works only for strongly connected graph
        static int i {0};
        i++;
        static int time {0};
        static bool* visitedArr = new bool [this->vertexSize] {};
        static int* startArr = new int [this->vertexSize] {};
        static int* finishArr = new int [this->vertexSize] {};
        if (i == 0) {
            for (int i = 0; i < this->vertexSize; i++) {
                visitedArr[i] = false;
                startArr[i] = 0;
                finishArr[i] = 0;
            }
        }

        visitedArr[startVertex] = true;
        startArr[startVertex] = time++;
        cout << startVertex << " " << std::flush;

        if (this->vertexArray[startVertex] != nullptr) {
            Node* head = this->vertexArray[startVertex];
            while (head != nullptr) {
                if (!(visitedArr[head->data])) {
                    this->getTraverseTime(head->data, 1);
                }
                head = head->next;
            }
        }

        finishArr[startVertex] = time++;
        if (n == 0) {
            delete [] visitedArr;
            cout << endl;
            return vector<int*> {startArr,finishArr};
        } else {
            return vector<int*> {nullptr,nullptr};
        }
    }  

    vector<int> dfsByStack(const int startIndex) {
        // Works only for strongly connected graph
        stack<int> vertexStack {};
        vector<bool> visitedArray (this->vertexSize, false);
        vector<int> dfsArray (this->vertexSize, -1);
        
        int index = startIndex;
        int i = 0;
        vertexStack.push(index);
        visitedArray[index] = true;
        
        while (!(vertexStack.empty())) {       
            index = vertexStack.top();
            dfsArray[i++] = index;
            vertexStack.pop();

            Node* head = this->vertexArray[index];
            while (head != nullptr) {
                if (!(visitedArray[head->data])) {
                    vertexStack.push(head->data);
                    visitedArray[head->data] = true;
                }
                head = head->next;
            }
        }   
        return dfsArray;
    }

    vector<vector<string>> classifyEdges(const int index, int n = 0) {
        // works only for strongly connected graphs
        static int* colorArray = new int [this->vertexSize] {};
        static int* startArray = new int [this->vertexSize] {};
        static int** dft = new int* [this->vertexSize] {};
        // without using dft, we could have used stack or start time difference of 1
        // to remember the parent of a node
        static int i {0};
        static int time {0};
        i++;
        if (i == 1) {
            for (int j = 0; j < this->vertexSize; j++) {
                dft[j] = new int [this->vertexSize] {};
            }
        }
        static vector<string> treeEdge {};
        static vector<string> backEdge {};
        static vector<string> crossEdge {};
        static vector<string> forwardEdge {};

        // set the vertex as visited but not backtracked
        colorArray[index] = 1;
        startArray[index] = time++;

        if (this->vertexArray[index] == nullptr) {
            cout << index << " " << std::flush;
        } else {
            Node* head = this->vertexArray[index];
            cout << index << " " << std::flush;
            while (head != nullptr) {
                if (colorArray[head->data] == 0) {
                    dft[index][head->data] = 1; // a tree edge now
                    string te = std::to_string(index) + string(" --> ") + std::to_string(head->data);
                    treeEdge.push_back(te);
                    this->classifyEdges(head->data, 1);
                }
                if (dft[index][head->data] == 0 && colorArray[head->data] == 1) {
                    string be = std::to_string(index) + string(" --> ") + std::to_string(head->data);
                    backEdge.push_back(be);
                }
                if (dft[index][head->data] == 0 && colorArray[head->data] == 2 && startArray[index] > startArray[head->data]) {
                    string ce = std::to_string(index) + string(" --> ") + std::to_string(head->data);
                    crossEdge.push_back(ce);
                }
                if (dft[index][head->data] == 0 && colorArray[head->data] == 2 && startArray[index] < startArray[head->data]) {
                    string fe = std::to_string(index) + string(" --> ") + std::to_string(head->data);
                    forwardEdge.push_back(fe);
                }
                head = head->next;
            }
        }

        // set the vertex as visited and backtracked
        colorArray[index] = 2;

        if (n == 0) {
            cout << endl;
            return vector<vector<string>> {treeEdge, backEdge, crossEdge, forwardEdge};
        } else {
            return vector<vector<string>> {};
        }
    }

};


int main() {
    Matrix* matrix = new Matrix {"matrixFile.txt"};
    //matrix->printMatrix();

    GraphList* graphList = new GraphList {matrix};
    //graphList->printGraph();

    vector<vector<string>> res = graphList->classifyEdges(0);

    for (auto i: res) {
        for (auto j: i) {
            cout << j << ", ";
        }
        cout << endl;
    }    

    delete graphList;
    delete matrix;
    
    return 0;
}