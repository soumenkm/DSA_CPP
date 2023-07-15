#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

class MinHeap {
private:
    int maxSize {0};
    int length {0};
    int* dataArr {nullptr};

public:
    MinHeap(const int _maxSize = 15) {
        this->maxSize = _maxSize;
        this->length = 0;
        this->dataArr = new int [this->maxSize];
        for (int i = 0; i < this->maxSize; i++) {
            this->dataArr[i] = -1;
        }
    }
    ~MinHeap() {
        delete [] this->dataArr;
    }
    void assignHeap(const int* const arr, int size) {
        for (int i = 0; i < size; i++) {
            this->dataArr[i] = arr[i];
        }
        this->length = size;
    }
    void printHeap() {
        for (int i = 0; i < this->length; i++) {
            cout << this->dataArr[i] << " ";
        }
        cout << "END" << endl;
    }

    int getLeftChild(const int index) {
        return 2*index+1;
    }
    int getRightChild(const int index) {
        return 2*index+2;
    }
    int getParent(const int index) {
        int parentIndex = std::ceil(index/2.0) - 1;
        return parentIndex;
    }
    void swap(const int idxa, const int idxb) {
        int temp = this->dataArr[idxa];
        this->dataArr[idxa] = this->dataArr[idxb];
        this->dataArr[idxb] = temp;
    }
    static int getMinOfArray(const int* const arr, const int size) {
        int min = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] < min) {
                min = arr[i];
            }
        }
        return min;
    }

    void heapify(const int rootIndex) {
        // the LST and RST are already min heap and root is to be fixed
        int lstRootIndex = this->getLeftChild(rootIndex);
        int rstRootIndex = this->getRightChild(rootIndex);
        
        if (lstRootIndex > this->length - 1 && rstRootIndex > this->length - 1) {
            // it is leaf node
            return;
        } else if (lstRootIndex < this->length && rstRootIndex > this->length - 1) {
            // only left child exist but right child doesn't exist
            if (this->dataArr[rootIndex] <= this->dataArr[lstRootIndex]) {
                // already min heap so simply return
                return;
            } else {
                // left is guranteed to be a leaf node in this case as heap is CBT
                this->swap(rootIndex, lstRootIndex);
                return;
            }

        } else {
            // both left and right child exist in min heap
            int treeRootArr[] {this->dataArr[rootIndex],
            this->dataArr[lstRootIndex], this->dataArr[rstRootIndex]};
            
            int min = MinHeap::getMinOfArray(treeRootArr, 3);

            if (this->dataArr[rootIndex] == min) {
                // already min heap so simple return
                return;
            } else if (this->dataArr[lstRootIndex] == min) {
                // root to be replaced by left as left is the min
                // and min always becomes root in min heap
                this->swap(rootIndex, lstRootIndex);
                this->heapify(lstRootIndex);
            } else if (this->dataArr[rstRootIndex] == min) {
                // root to be replaced by right as right is the min
                // and min always becomes root in min heap
                this->swap(rootIndex, rstRootIndex);
                this->heapify(rstRootIndex);
            } else {
                cout << "Something went wrong" << endl;
            }
        }

    }

    void buildHeap(const int* const arr, const int size) {
        if (size > this->maxSize) {
            this->maxSize = size;
        }
        // assign the array to heap
        this->assignHeap(arr, size);

        // heapify from bottom to top starting from internal node
        int internalIndex = std::ceil(size/2.0) - 1;
        for (int i = internalIndex; i >= 0; i--) {
            // this->printHeap();
            this->heapify(i);
        }
    }

    void decreaseKey(const int index) {
        // Move up the index to top levels if required 
        if (index == 0) {
            // if the index is already at top level then return
            return;
        } else {
            // else recursively decrease the key until top level
            int parentIndex = this->getParent(index);
            if (this->dataArr[index] >= this->dataArr[parentIndex]) {
                // stop when there is no nore to decrease the key
                return;
            } else {
                this->swap(parentIndex, index);
                decreaseKey(parentIndex);
            }
        }
    }

    void insertNode(const int elem){
        if (this->length == this->maxSize) {
            (this->maxSize)++;
        }
        if (this->length > this->maxSize) {
            cout << "Something went wrong!" << endl;
        }
        
        // Insert the node at the last place
        int insertAt = this->length;
        this->dataArr[insertAt] = elem;
        (this->length)++;

        // Adjust the values till the top level
        int childIndex = this->length - 1;
        decreaseKey(childIndex);
    }

    void buildHeapByRepeatedInsertion(const int* const arr, const int size) {
        for (int i = 0; i < size; i++) {
            this->insertNode(arr[i]);
        }
    }
};

int main() {
    MinHeap* minHeap = new MinHeap {};
    MinHeap* minHeap2 = new MinHeap {};

    int arr[] = {5,10,1,20,6,17,15,2,4,3}; int size = sizeof(arr)/sizeof(int);
    
    minHeap->buildHeap(arr, size);
    minHeap->printHeap();

    minHeap2->buildHeapByRepeatedInsertion(arr, size);
    minHeap2->printHeap();

    delete minHeap; // deallocate the object
    delete minHeap2;

    return 0;
}