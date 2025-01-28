// Name: Diya Goyal
// Roll no: 102215255
// Question: Q2: Implement the Heapsort algorithm to arrange numbers in descending order.
// Acknowledgement: took help from GitHub Copilot

#include <iostream>
#include <vector>
using namespace std;

// Heapify subtree rooted at 'i' up to size 'n'
void minHeapify(vector<int> &arr, int n, int i) {
    int left = 2*i + 1;
    int right = 2*i + 2;
    int smallest = i;

    if (left < n && arr[left] < arr[smallest]) smallest = left;
    if (right < n && arr[right] < arr[smallest]) smallest = right;

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

// Build a min-heap
void buildMinHeap(vector<int> &arr) {
    int n = arr.size();
    for (int i = n/2 - 1; i >= 0; i--) {
        minHeapify(arr, n, i);
    }
}

// Heapsort for descending order
void heapSort(vector<int> &arr) {
    buildMinHeap(arr);
    for (int i = arr.size() - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        minHeapify(arr, i, 0);
    }
}

int main(){
    vector<int> arr = {30, 10, 50, 20, 60, 40};
    heapSort(arr);
    for (int x : arr) cout << x << " ";
    cout << endl;
    return 0;
}
