/*
Name: Diya Goyal
Roll Number: 102215255
Question: 4. Boyer Moore algorithm.
Acknowledgments: Geeks for geeks,classmates
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int ALPHABET_SIZE = 256;
// Build the bad character heuristic table
void badCharHeuristic(const string& pattern, vector<int>& badChar) {
 for (int i = 0; i < ALPHABET_SIZE; i++)
 badChar[i] = -1;
 for (int i = 0; i < pattern.size(); i++)
 badChar[(int)pattern[i]] = i;
}
// Boyer-Moore search using bad character heuristic
vector<int> boyerMooreSearch(const string& text, const string&
pattern) {
 int m = pattern.size();
 int n = text.size();
 vector<int> badChar(ALPHABET_SIZE);
 vector<int> result;
 badCharHeuristic(pattern, badChar);
 int shift = 0;
 while (shift <= (n - m)) {
 int j = m - 1;
 while (j >= 0 && pattern[j] == text[shift + j])
 j--;
 if (j < 0) {
 result.push_back(shift);
 shift += (shift + m < n) ? m - badChar[text[shift + m]] :
1;
 } else {
 shift += max(1, j - badChar[text[shift + j]]);
 }
 }
 return result;
}
// Main function to test
int main() {
 string text, pattern;
 cout << "Enter the text: ";
 getline(cin, text);
 cout << "Enter the pattern: ";
 getline(cin, pattern);
 vector<int> matches = boyerMooreSearch(text, pattern);
 if (matches.empty())
 cout << "Pattern not found." << endl;
 else {
 cout << "Pattern found at index/indices: ";
 for (int idx : matches) cout << idx << " ";
 cout << endl;
 }
 return 0;
}
