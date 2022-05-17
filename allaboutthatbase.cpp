#include <iostream>
#include <string>
#include <optional>
#include <cstdint>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::optional;
using std::string;

constexpr uint32_t max_int = -1;

optional<uint32_t> parse(const string& s, uint32_t base) {
  const uint32_t max_int_div_base = max_int / base;

  uint32_t value = 0;

  for (char c : s) {
    if (value > max_int_div_base) return {};
    value *= base;
    
    uint32_t addend;
    if (isdigit(c)) {
      addend = c - '0';
    }
    else {
      addend = c - 'a' + 10;
    }
    if (base == 1) {
      if (addend != base) return {};
    }
    else {
      if (addend >= base) return {};
    }

    if (value > max_int - addend) return {};
    value += addend;
  }

  return value;
}

uint64_t eval(uint32_t lhs, char op, uint32_t rhs) {
  switch (op) {
  case '+': return lhs + rhs;
  case '-': return lhs - rhs;
  case '*': return lhs * rhs;
  default:  return lhs % rhs ? (uint64_t)max_int + 1 : lhs / rhs;
  }
}

struct Eq {
  string lhs;
  char op;
  string rhs;
  string result;
};

bool check(const Eq& eq, uint32_t base) {
  auto lhs = parse(eq.lhs, base);
  auto rhs = parse(eq.rhs, base);
  auto result = parse(eq.result, base);

  return lhs && rhs && result && eval(*lhs, eq.op, *rhs) == result;
}

int main() {
  char skip;
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    Eq eq;
    cin >> eq.lhs >> eq.op >> eq.rhs >> skip >> eq.result;

    bool invalid = true;
    for (int b = 1; b <= 36; ++b) {
      if (check(eq, b)) {
        invalid = false;
        if (b < 10)
          cout << b;
        else if (b == 36)
          cout << '0';
        else
          cout << (char)('a' + b - 10);
      }
    }
    if (invalid) {
      cout << "invalid\n";
    }
    else {
      cout << '\n';
    }
  }
}
