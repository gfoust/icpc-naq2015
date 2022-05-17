#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
using namespace std;

map<string, string> languageSpokenBy;
map<string, vector<string>> peopleWhoUnderstand;
map<string, vector<string>> arrows;
map<string, bool> haveSeen;
vector<vector<string>> componentList;

void depthFirstSearch(string name, vector<string>& visited) {
  if (! haveSeen[name]) {
    haveSeen[name] = true;
    for (auto destination : arrows[name]) {
      depthFirstSearch(destination, visited);
    }
    visited.push_back(name);
  }
}

void flipArrows() {
  map<string, vector<string>> backarrows;
  for (auto& [start, destinationList] : arrows) {
    for (auto& destination : destinationList) {
      backarrows[destination].push_back(start);
    }
  }
  arrows = move(backarrows);
}

void makeArrows() {
  for (auto& [name, language] : languageSpokenBy) {
    arrows[name] = peopleWhoUnderstand[language];
  }
}

void findComponents() {
  makeArrows();
  vector<string> stack;
  for (auto& [name, destinationList] : arrows) {
    depthFirstSearch(name, stack);
  }
  flipArrows();
  haveSeen.clear();
  while (!stack.empty()) {
    vector<string> component;
    depthFirstSearch(stack.back(), component);
    stack.pop_back();
    if (!component.empty()) {
      componentList.push_back(component);
    }
  }
}

void getInput() {
  int howManyPeople;
  cin >> howManyPeople;
  cin.ignore(1000, '\n');
  for (int i = 0; i < howManyPeople; ++i) {
    string line;
    getline(cin, line);
    istringstream lin(line);

    string name;
    lin >> name;

    string language;
    lin >> language;
    languageSpokenBy[name] = language;

    peopleWhoUnderstand[language].push_back(name);

    while (lin >> language) {
      peopleWhoUnderstand[language].push_back(name);
    }
  }
}

int biggestComponentSize() {
  int biggest = 0;

  for (auto& component : componentList) {
    if (component.size() > biggest) {
      biggest = component.size();
    }
  }

  return biggest;
}

int main() {
  getInput();
  findComponents();
  cout << arrows.size() - biggestComponentSize() << endl;
}
