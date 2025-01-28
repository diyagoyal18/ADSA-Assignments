// Name: Diya Goyal
// Roll no: 102215255
// Question:Implement a min-priority queue with a min-heap. The program should have functions for the following operations:
// HEAP-MINIMUM to get the element with the smallest key,
// HEAP- EXTRACT-MIN to remove and return the element with the smallest key,
// HEAP-DECREASE-KEY decreases the value of the element to a new value, and
// MIN-HEAP-INSERT to insert the element.
// Acknowledgement: took help from GitHub Copilot
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;
class MinPriorityQueue {
private:
    vector<int> heap;
    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap[i] < heap[parent]) {
                swap(heap[i], heap[parent]);
                i = parent;
            } else {
                break;
            }
        }
    }
    void heapifyDown(int i) {
        int size = heap.size();
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;
            if (left < size && heap[left] < heap[smallest]) smallest = left;
            if (right < size && heap[right] < heap[smallest]) smallest = right;
            if (smallest != i) {
                swap(heap[i], heap[smallest]);
                i = smallest;
            } else {
                break;
            }
        }
    }
public:
    int heap_minimum() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        return heap[0];
    }
    int heap_extract_min() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return minVal;
    }
    void heap_decrease_key(int i, int newVal) {
        if (i < 0 || i >= (int)heap.size()) throw runtime_error("Index out of range");
        if (newVal > heap[i]) throw runtime_error("New value is greater than current value");
        heap[i] = newVal;
        heapifyUp(i);
    }
    void min_heap_insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }
    void printHeap() {
        for (int val : heap) cout << val << " ";
        cout << endl;
    }
};
int main() {
    MinPriorityQueue mpq;
    mpq.min_heap_insert(10);
    mpq.min_heap_insert(5);
    mpq.min_heap_insert(20);
    mpq.min_heap_insert(2);
    cout << "Minimum: " << mpq.heap_minimum() << endl;
    cout << "Extract Min: " << mpq.heap_extract_min() << endl;
    mpq.printHeap();
    mpq.heap_decrease_key(1, 1);
    mpq.printHeap();
    return 0;
}
