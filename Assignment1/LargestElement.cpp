// Name: Diya Goyal
// Roll no: 102215255
// Question: Q3: Write a program to find the largest element in an unsorted array.
// Acknowledgement: took help from GitHub Copilot

#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 90, 30, 70, 20, 50};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    int largest = arr[0];
    for(int i = 1; i < n; i++) {
        if(arr[i] > largest) {
            largest = arr[i];
        }
    }
    
    cout << "Largest element: " << largest << endl;
    return 0;
}