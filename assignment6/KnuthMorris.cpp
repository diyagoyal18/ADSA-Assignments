/*
Name: Diya Goyal
Roll Number: 102215255
Question: 3. Knuth-Morris-Pratt
Acknowledgments: Geeks for geeks,classmates,
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// Preprocess the pattern to create the LPS (Longest Prefix Suffix)array
vector<int> computeLPSArray(const string& pattern) {
 int M = pattern.length();
 vector<int> lps(M);
 int len = 0;
 lps[0] = 0;
 int i = 1;
 while (i < M) {
 if (pattern[i] == pattern[len]) {
 len++;
 lps[i] = len;
 i++;
 } else {
 if (len != 0)
 len = lps[len - 1];
 else {
 lps[i] = 0;
 i++;
 }
 }
 }
 return lps;
}
// Perform KMP string matching
vector<int> KMPSearch(const string& text, const string& pattern) {
 int N = text.length();
 int M = pattern.length();
 vector<int> lps = computeLPSArray(pattern);
 vector<int> matches;
 int i = 0, j = 0;
 while (i < N) {
 if (pattern[j] == text[i]) {
 i++; j++;
 }
 if (j == M) {
 matches.push_back(i - j);
 j = lps[j - 1];
 } else if (i < N && pattern[j] != text[i]) {
 if (j != 0)
 j = lps[j - 1];
 else
 i++;
 }
 }
 return matches;
}
// Main function for testing
int main() {
 string text, pattern;
 cout << "Enter the text: ";
 getline(cin, text);
 cout << "Enter the pattern to search: ";
 getline(cin, pattern);
 vector<int> result = KMPSearch(text, pattern);
 if (result.empty())
 cout << "Pattern not found." << endl;
 else {
 cout << "Pattern found at index/indices: ";
 for (int idx : result) cout << idx << " ";
 cout << endl;
 }
 return 0;
}