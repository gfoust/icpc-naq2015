#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::priority_queue;
using std::vector;

using Positions = std::int32_t;

struct State {
  Positions pos;
  int time;
};

bool operator <(State a, State b) {
  return a.time > b.time;
}

int min(vector<int> times) {
  int count = times.size();
  priority_queue<State> states;
  map<Positions, int> fastest;
  Positions init = (1 << count) - 1;

  auto maybe_add_state = [&](Positions pos, int time) {
    auto [p, inserted] = fastest.insert({ pos, time });
    if (inserted || time < p->second) {
      p->second = time;
      states.push({ pos, time });
    }
  };

  maybe_add_state(init, 0);

  while (!states.empty()) {
    State cur = states.top();
    states.pop();
    if (cur.pos == 0) {
      return cur.time;
    }
    if (cur.time == fastest[cur.pos]) {
      if (cur.pos < 0) {
        int pos = -cur.pos;
        // find one that is off and turn it on
        for (int i = 0; i < count; ++i) {
          if ((pos & 1 << i) == 0) {
            int newpos = pos | 1 << i;
            int time = cur.time + times[i];
            maybe_add_state(newpos, time);
          }
        }
      }
      else {
        int pos = cur.pos;
        // find two that are on and turn them off
        for (int i = 0; i < count; ++i) {
          if ((pos & 1 << i) != 0) {
            for (int j = i + 1; j < count; ++j) {
              if ((pos & 1 << j) != 0) {
                int newpos = pos & ~(1 << i) & ~(1 << j);
                int time = cur.time + std::max(times[i], times[j]);
                maybe_add_state(-newpos, time);
              }
            }
          }
        }
      }
    }
  }
  // unreachable
  return 0;
}

int main() {
  int n;
  cin >> n;
  vector<int> times(n);
  for (int i = 0; i < n; ++i) {
    cin >> times[i];
  }
  cout << min(std::move(times)) << endl;
}