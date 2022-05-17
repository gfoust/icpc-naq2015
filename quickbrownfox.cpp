#include <iostream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

vector<int> count(string s) {
  vector<int> cs(26);
  for (char c : s) {
    if (isalpha(c)) {
      ++cs[tolower(c) - 'a'];
    }
  }
  return cs;
}

int main() {
  int n;
  cin >> n;
  cin.ignore(100, '\n');
  for (int i = 0; i < n; ++i) {
    string line;
    getline(cin, line);
    auto cs = count(move(line));
    bool all = true;
    for (char c = 'a'; c <= 'z'; ++c) {
      if (cs[c - 'a'] == 0) {
        if (all) {
          cout << "missing ";
          all = false;
        }
        cout << c;
      }
    }
    if (all) {
      cout << "pangram\n";
    }
    else {
      cout << '\n';
    }
  }
}