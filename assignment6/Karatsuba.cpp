
/*
Name: Diya Goyal
Roll Number: 102215255
Question: 2. Karatsuba algorithm
Acknowledgments: Geeks for geeks,classmates,
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// Helper to add two large numbers
string addStrings(string a, string b) {
 if (a.length() < b.length()) swap(a, b);
 int carry = 0;
 string result = "";
 reverse(a.begin(), a.end());
 reverse(b.begin(), b.end());
 for (size_t i = 0; i < a.length(); i++) {
 int digitA = a[i] - '0';
 int digitB = i < b.length() ? b[i] - '0' : 0;
 int sum = digitA + digitB + carry;
 result += (sum % 10 + '0');
 carry = sum / 10;
 }
 if (carry) result += (carry + '0');
 reverse(result.begin(), result.end());
 return result;
}
// Helper to subtract two large numbers
string subtractStrings(string a, string b) {
 while (b.length() < a.length()) b = '0' + b;
 string result = "";
 int carry = 0;
 for (int i = a.length() - 1; i >= 0; i--) {
 int digitA = a[i] - '0';
 int digitB = b[i] - '0' + carry;
 if (digitA < digitB) {
 digitA += 10;
 carry = 1;
 } else {
 carry = 0;
 }
 result = char(digitA - digitB + '0') + result;
 }
 // Remove leading zeros
 result.erase(0, result.find_first_not_of('0'));
 return result.empty() ? "0" : result;
}
// Pad with zeros
string padZero(string s, int n) {
 while (s.length() < n) s = "0" + s;
 return s;
}
// Karatsuba multiplication
string karatsuba(string x, string y) {
 int n = max(x.length(), y.length());
 if (n == 1) return to_string((x[0] - '0') * (y[0] - '0'));
 n += n % 2; // Make n even
 x = padZero(x, n);
 y = padZero(y, n);
 int mid = n / 2;
 string xL = x.substr(0, mid);
 string xR = x.substr(mid);
 string yL = y.substr(0, mid);
 string yR = y.substr(mid);
 string P1 = karatsuba(xL, yL);
 string P2 = karatsuba(xR, yR);
 string P3 = karatsuba(addStrings(xL, xR), addStrings(yL, yR));
 string middle = subtractStrings(subtractStrings(P3, P1), P2);
 // Add trailing zeros to simulate multiplication by powers of 10
 P1.append(2 * (n - mid), '0');
 middle.append(n - mid, '0');
 return addStrings(addStrings(P1, middle), P2);
}
int main() {
 string num1, num2;
 cout << "Enter first number: ";
 cin >> num1;
 cout << "Enter second number: ";
 cin >> num2;
 string result = karatsuba(num1, num2);
 cout << "Karatsuba Multiplication Result: " << result << endl;
 return 0;
}