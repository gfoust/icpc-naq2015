#include <array>
#include <iostream>
#include <vector>
#include <utility>
#include <cstdint>
using std::cin;
using std::cout;
using std::endl;
using std::int64_t;

constexpr int64_t OFF = 210;
constexpr int64_t SIZE = OFF * 2 + 1;

struct Vec { int64_t x, y; };

struct Grid {
  std::vector<std::array<int64_t, SIZE>> data;
  int64_t dummy;

  Grid() : data(SIZE), dummy{ 0 } {
  }

  int64_t& at(int64_t r, int64_t c) {
	if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) {
	  return dummy;
	}
	return data[r][c];
  }
};

int64_t numZeroSums(std::vector<Vec> vecs) {
  Grid cur, prev;

  for (Vec vec : vecs) {
	std::swap(cur, prev);
	for (int64_t r = 0; r < SIZE; ++r) {
	  for (int64_t c = 0; c < SIZE; ++c) {
		cur.at(r, c) = prev.at(r, c) + prev.at(r - vec.x, c - vec.y);
	  }
	}
	++cur.at(vec.x + OFF, vec.y + OFF);
  }

  return cur.at(OFF, OFF);
}

int main() {
  int64_t n;
  cin >> n;
  std::vector<Vec> vecs;
  for (int64_t i = 0; i < n; ++i) {
	Vec vec;
	cin >> vec.x >> vec.y;
	vecs.push_back(vec);
  }
  cout << numZeroSums(std::move(vecs)) << endl;
}

