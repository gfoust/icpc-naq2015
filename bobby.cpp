#include <iostream>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;
using std::pow;

int countbits(int bits) {
  int count = 0;
  for (int i = 0, b = 1; i < 20; ++i, b <<= 1) {
    if (bits & b) {
      ++count;
    }
  }
  return count;
}

bool goforit(double winrolls, double totalrolls, int wingames, int totalgames, int weight) {
  double winprob = winrolls / totalrolls;
  double loseprob = (totalrolls - winrolls) / totalrolls;
  
  double prob = 0;
  for (int i = 0; i < 1 << totalgames; ++i) {
    int wins = countbits(i);
    if (wins >= wingames) {
      prob += pow(winprob, wins) * pow(loseprob, (totalgames - wins));
    }
  }

  return prob * weight > 1;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int r, s, x, y, w;
    cin >> r >> s >> x >> y >> w;
    if (goforit(s - r + 1, s, x, y, w)) {
      cout << "yes\n";
    }
    else {
      cout << "no\n";
    }
  }
}