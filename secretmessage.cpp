#include <cmath>
#include <iostream>
#include <string>
using std::cin; 
using std::cout;
using std::endl;
using std::string;


int main() {
  string message;
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> message;
    int k = std::ceil(std::sqrt(message.size()));
    for (int c = 0; c < k; ++c) {
      for (int r = k - 1; r >= 0; --r) {
        int i = r * k + c;
        if (i < message.size()) {
          cout << message[i];
        }
      }
    }
    cout << endl;
  }
}