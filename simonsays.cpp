#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::string_view;

int main() {
  int n;
  cin >> n;
  cin.ignore(10000, '\n');
  for (int i = 0; i < n; ++i) {
    string line;
    getline(cin, line);
    if (string_view(line.data(), 10) == "Simon says") {
      cout << string_view(line.data() + 10) << endl;
    }
  }
}