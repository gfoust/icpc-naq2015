#include <array>
#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

enum Result : uint8_t {
  Lose, Win, Huh
};

constexpr int SIZE = 500;

using Grid = std::vector<std::array<Result, SIZE + 1>>;
Grid harry(SIZE + 1);
Grid vicky(SIZE + 1);

void solve(int height, int width) {
  Result result = Lose;
  for (int r = 1; result == Lose && r < height; ++r) {
    if (vicky[r][width] == Lose && vicky[height - r][width] == Lose) {
      result = Win;
    }
  }
  harry[height][width] = result;

  result = Lose;
  for (int c = 1; result == Lose && c < width; ++c) {
    if (harry[height][c] == Lose && harry[height][width - c] == Lose) {
      result = Win;
    }
  }
  vicky[height][width] = result;

}

void build() {
  for (int h = 1; h <= SIZE; ++h) {
    for (int w = 1; w <= SIZE; ++w) {
      solve(h, w);
    }
  }
}

int main() {
  build();
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int width, height;
    string name;
    cin >> width >> height >> name;
    if (name == "Harry") {
      if (harry[height][width] == Win) {
        cout << "Harry can win\n";
      }
      else {
        cout << "Harry cannot win\n";
      }
    }
    else {
      if (vicky[height][width] == Win) {
        cout << "Vicky can win\n";
      }
      else {
        cout << "Vicky cannot win\n";
      }
    }
  }
}

