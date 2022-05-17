#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <optional>
#include <vector>
using namespace std;

multimap<string, string> connections;

void input() {
	int N;
	cin >> N;
	while (cin.get() != '\n');
	for (int i = 0; i < N; ++i) {
		string line;
		getline(cin, line);
		stringstream l_in(line);
		string from;
		l_in >> from;
		string to;
		while (l_in >> to) {
			connections.insert({ from, to });
			connections.insert({ to, from });
		}
	}
}

optional<vector<string>> findPath(vector<string> soFar, const string& dest) {
	auto range = connections.equal_range(soFar.back());
	for (auto i = range.first; i != range.second; ++i) {
		auto [from, to] = *i;
		if (to == dest) {
			soFar.push_back(to);
			return soFar;
		}
		else if (find(begin(soFar), end(soFar), to) == end(soFar)) {
			soFar.push_back(to);
			auto result = findPath(soFar, dest);
			if (result) {
				return result;
			}
			soFar.pop_back();
		}
	}
	return nullopt;
}

int main() {
	input();
	string from, to;
	cin >> from >> to;
	auto result = findPath({ from }, to);
	if (result) {
		bool start = true;
		for (string name : *result) {
			if (start) start = false;
			else cout << ' ';
			cout << name;
		}
		cout << endl;
	}
	else {
		cout << "no route found" << endl;
	}
}
