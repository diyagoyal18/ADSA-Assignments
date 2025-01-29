#include <iostream>      // For basic I/O
#include <vector>        // For storing heap elements using a dynamic array
using namespace std;     // Standard namespace

class BinaryHeap {
private:
    vector<int> heap;                                       // Our heap container

    void siftUp(int index) {
        // Moves an inserted element up to maintain heap property
        while (index > 0) {                                 // While not at the root
            int parent = (index - 1) / 2;                   // Calculate parent index
            if (heap[index] <= heap[parent]) break;         // If child no bigger, stop
            swap(heap[index], heap[parent]);                // Otherwise swap with parent
            index = parent;                                 // Continue from new position
        }
    }

    void siftDown(int index) {
        // Moves a swapped-down element down to maintain heap property
        int size = heap.size();
        while (true) {
            int left = 2 * index + 1;                       // Left child index
            int right = 2 * index + 2;                      // Right child index
            int largest = index;                            // Assume current is largest

            // Compare with left child
            if (left < size && heap[left] > heap[largest]) {
                largest = left;
            }

            // Compare with right child
            if (right < size && heap[right] > heap[largest]) {
                largest = right;
            }

            if (largest == index) break;                    // If already largest, stop
            swap(heap[index], heap[largest]);               // Swap down
            index = largest;                                // Continue from new position
        }
    }

public:
    void push(int value) {
        // Inserts new value and re-heapifies
        heap.push_back(value);                              // Add at end
        siftUp(heap.size() - 1);                            // Restore heap upward
    }

    void pop() {
        // Removes the top (max) and re-heapifies
        if (heap.empty()) return;                           // Nothing to remove
        heap[0] = heap.back();                              // Move last element to root
        heap.pop_back();                                    // Remove last element
        if (!heap.empty()) siftDown(0);                     // Restore heap downward
    }

    int top() {
        // Returns the top (max) element
        if (!heap.empty()) return heap[0];                  // If not empty, return top
        return -1;                                          // Return -1 if empty
    }

    int size() {
        // Returns current size of heap
        return heap.size();
    }
};

// Example usage for demonstration
int main() {
    BinaryHeap bh;
    bh.push(10);
    bh.push(5);
    bh.push(20);
    bh.push(15);

    cout << "Top: " << bh.top() << endl;   // Should display max element
    bh.pop();
    cout << "Top after pop: " << bh.top() << endl;

    return 0;
}