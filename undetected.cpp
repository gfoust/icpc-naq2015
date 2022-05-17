#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::set;
using std::sqrt;
using std::stack;
using std::vector;

using Graph = map<int, set<int>>;

constexpr int WIDTH = 200;
constexpr int HEIGHT = 300;

bool connected(Graph& graph, int begin, int end, int max) {
  set<int> visited;
  stack<int> nodes;

  visited.insert(begin);
  nodes.push(begin);

  while (!nodes.empty()) {
    int node = nodes.top();
    nodes.pop();

    for (int next : graph[node]) {
      if (next == end) {
        return true;
      }
      if (next < max) {
        auto [p, inserted] = visited.insert(next);
        if (inserted) {
          nodes.push(next);
        }
      }
    }
  }

  return false;
}

struct Circle {
  double x, y, r;
};

double distanceBetween(Circle& a, Circle& b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return sqrt(dx*dx + dy*dy);
}

Graph build(vector<Circle>& circles) {
  Graph graph;
  int begin = circles.size();
  int end = circles.size() + 1;
  for (int i = 0; i < circles.size(); ++i) {
    Circle& circle = circles[i];
    if (circle.r > circle.x) {
      graph[begin].insert(i);
    }
    for (int j = 0; j < circles.size(); ++j) {
      if (distanceBetween(circle, circles[j]) < circle.r + circles[j].r) {
        graph[i].insert(j);
        graph[j].insert(i);
      }
    }
    if (WIDTH - circle.r < circle.x) {
      graph[i].insert(end);
    }
  }
  return graph;
}

int main() {
  int n;
  cin >> n;

  vector<Circle> circles(n);
  for (int i = 0; i < n; ++i) {
    cin >> circles[i].x >> circles[i].y >> circles[i].r;
  }
  Graph graph = build(circles);
  int k = circles.size();
  int begin = circles.size();
  int end = circles.size() + 1;
  while (connected(graph, begin, end, k)) {
    --k;
  }
  cout << k << endl;
}
