#ifndef HEAP_H
#define HEAP_H

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

    bool isEmpty() {
        if (this->length == 0) {
            return true;
        } else if (this->length > 0 && this->length <= this->maxSize) {
            return false;
        } else {
            throw std::runtime_error("Heap size out of range!");
        }
    }

    bool isFull() {
        if (this->length >= 0 && this->length == this->maxSize) {
            return true;
        } else if (this->length >= 0 && this->length < this->maxSize) {
            return false;
        } else {
            throw std::runtime_error("Heap size out of range!");
        }
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

    static void printArray(const int* const arr, const int size) {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
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

    static int getKthMinOfArray(const int* const arr, const int size, const int k) {
        // k = 1 means 1st min, k = 2 means 2nd min and so on ...
        // Create a copy of the input array
        int* tempArr = new int[size];
        std::copy(arr, arr + size, tempArr);

        // Sort the array in ascending order
        std::sort(tempArr, tempArr + size);

        // Return the kth smallest element
        int kthMin = tempArr[k - 1];
        delete[] tempArr;
        return kthMin;
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

    void percolateUp(const int index) {
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
                percolateUp(parentIndex);
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
        this->percolateUp(childIndex);
    }

    void buildHeapByRepeatedInsertion(const int* const arr, const int size) {
        for (int i = 0; i < size; i++) {
            this->insertNode(arr[i]);
        }
    }

    int deleteMin() {
        // Replace the root with the last element
        int min = this->dataArr[0]; // store it for return
        this->swap(0, this->length - 1);

        // Delete the last node
        this->dataArr[this->length - 1] = -1; // reset to -1
        (this->length)--;

        // Heapify the tree now
        this->heapify(0);

        // Return the deleted element
        return min;
    }

    int findMin() {
        if (!(this->isEmpty())) {
            return this->dataArr[0];
        } else {
            return -1;
        }
    }

    int findMax() {
        // Max is present at leaf nodes
        int numLeafs = std::ceil(this->length/2.0);    
        int max = this->dataArr[this->length - 1];
        for (int i = 1; i < numLeafs; i++) {
            int current = this->dataArr[this->length - 1 - i];
            if (current > max) {
                max = current;
            }
        }
        return max;
    }

    int findKthMin(const int k) {
        // Kth min is present at most k-1 th level where level 0 is root
        // k = 1 means 1st minimum, k = 2 means 2nd minimum and so on ...
        int kthMin {-1};
        if (k > 0 && k <= this->length) {
            int numScan = static_cast<int>(std::pow(2, k)) - 1;
            int numElem = numScan > this->length ? this->length : numScan;
            kthMin = MinHeap::getKthMinOfArray(this->dataArr, numElem, k);
        } else {
            throw std::runtime_error("Invalid input k!");
        }
        return kthMin;
    }

    int* heapSort() {
        // Store the length and original heap
        int length = this->length;
        int* tempArr = new int[length] {};
        std::copy(this->dataArr, this->dataArr + length, tempArr);

        // delete the nodes from heap in place
        while (!(this->isEmpty())) {
            this->dataArr[this->length] = this->deleteMin(); // sort in place
        }

        // store it in another array
        int* sortedArr = new int[length] {};
        std::copy(this->dataArr, this->dataArr + length, sortedArr);

        // reset the heap to original
        std::copy(tempArr, tempArr + length, this->dataArr);
        delete [] tempArr;

        // return the sorted array
        return sortedArr;
    }

    int searchKey(const int key) {
        int index {-1};
        for (int i = 0; i < this->length; i++) {
            if (this->dataArr[i] == key) {
                index = i;
                break;
            }
        }
        return index;
    }

    void decreaseKey(const int oldKey, const int newKey) {
        if (newKey >= oldKey) {
            return;
        } else {
            // We provide the key value and not the index so search for key
            int index = this->searchKey(oldKey);
            
            // Replace the old key by new key
            this->dataArr[index] = newKey;

            // Adjust the keys till top level (percolate up)
            this->percolateUp(index);
        }
    }

    void increaseKey(const int oldKey, const int newKey) {
        if (newKey <= oldKey) {
            return;
        } else {
            // We provide the key value and not the index so search for key
            int index = this->searchKey(oldKey);
            
            // Replace the old key by new key
            this->dataArr[index] = newKey;
            
            // Adjust the keys till bottom level (heapify)
            this->heapify(index);
        }
    }

};

#endif
