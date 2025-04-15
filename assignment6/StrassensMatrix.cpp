/*
Name: Diya Goyal
Roll Number: 102215255
Question: 1: Strassen's matrix multiplication
Acknowledgments: Geeks for geeks,classmates
*/
#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<int> > Matrix;
Matrix add(Matrix A, Matrix B) {
 int n = A.size();
 Matrix result(n, vector<int>(n));
 for (int i = 0; i < n; i++)
 for (int j = 0; j < n; j++)
 result[i][j] = A[i][j] + B[i][j];
 return result;
}
Matrix subtract(Matrix A, Matrix B) {
 int n = A.size();
 Matrix result(n, vector<int>(n));
 for (int i = 0; i < n; i++)
 for (int j = 0; j < n; j++)
 result[i][j] = A[i][j] - B[i][j];
 return result;
}
Matrix strassen(Matrix A, Matrix B) {
 int n = A.size();
 Matrix result(n, vector<int>(n));
 if (n == 1) {
 result[0][0] = A[0][0] * B[0][0];
 return result;
 }
 int k = n / 2;
 Matrix A11(k, vector<int>(k)), A12(k, vector<int>(k)),
 A21(k, vector<int>(k)), A22(k, vector<int>(k)),
 B11(k, vector<int>(k)), B12(k, vector<int>(k)),
 B21(k, vector<int>(k)), B22(k, vector<int>(k));
 for (int i = 0; i < k; i++) {
 for (int j = 0; j < k; j++) {
 A11[i][j] = A[i][j];
 A12[i][j] = A[i][j + k];
 A21[i][j] = A[i + k][j];
 A22[i][j] = A[i + k][j + k];
 B11[i][j] = B[i][j];
 B12[i][j] = B[i][j + k];
 B21[i][j] = B[i + k][j];
 B22[i][j] = B[i + k][j + k];
 }
 }
 Matrix M1 = strassen(add(A11, A22), add(B11, B22));
 Matrix M2 = strassen(add(A21, A22), B11);
 Matrix M3 = strassen(A11, subtract(B12, B22));
 Matrix M4 = strassen(A22, subtract(B21, B11));
 Matrix M5 = strassen(add(A11, A12), B22);
 Matrix M6 = strassen(subtract(A21, A11), add(B11, B12));
 Matrix M7 = strassen(subtract(A12, A22), add(B21, B22));
 Matrix C11 = add(subtract(add(M1, M4), M5), M7);
 Matrix C12 = add(M3, M5);
 Matrix C21 = add(M2, M4);
 Matrix C22 = add(subtract(add(M1, M3), M2), M6);
 for (int i = 0; i < k; i++) {
 for (int j = 0; j < k; j++) {
 result[i][j] = C11[i][j];
 result[i][j + k] = C12[i][j];
 result[i + k][j] = C21[i][j];
 result[i + k][j + k] = C22[i][j];
 }
 }
 return result;
}
void printMatrix(Matrix A) {
 int n = A.size();
 for (int i = 0; i < n; i++) {
 for (int j = 0; j < n; j++)
 cout << A[i][j] << " ";
 cout << endl;
 }
}
int main() {
 int n = 2; // Matrix size (must be power of 2)
 Matrix A(n, vector<int>(n));
 Matrix B(n, vector<int>(n));
 cout << "Enter elements of Matrix A (" << n << "x" << n << ")\n";
 for (int i = 0; i < n; i++)
 for (int j = 0; j < n; j++)
 cin >> A[i][j];
 cout << "Enter elements of Matrix B (" << n << "x" << n << ")\n";
 for (int i = 0; i < n; i++)
 for (int j = 0; j < n; j++)
 cin >> B[i][j];
 Matrix C = strassen(A, B);
 cout << "Result of Strassen Multiplication:\n";
 printMatrix(C);
 return 0;
}