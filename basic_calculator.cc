#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

class Solution {
private:
  int Calculate(const std::string &expression, std::size_t &idx) {
    auto final_result{0};
    auto cur_result = GetOneNumber(expression, idx);
    while (idx < expression.length()) {
      if (expression[idx] == '+') {
        final_result += cur_result;
        idx++;
        cur_result = GetOneNumber(expression, idx);
      } else if (expression[idx] == '-') {
        final_result += cur_result;
        idx++;
        cur_result = -GetOneNumber(expression, idx);
      } else if (expression[idx] == '*') {
        idx++;
        cur_result *= GetOneNumber(expression, idx);
      } else if (expression[idx] == '/') {
        idx++;
        cur_result /= GetOneNumber(expression, idx);
      } else if (expression[idx] == ')') {
        idx++;
        break;
      } else if (expression[idx] == ' ') {
        idx++;
      } else {
        std::ostringstream oss;
        oss << "should not reach here; expression:" << expression
            << ",idx:" << idx << ",expression[idx]:" << expression[idx];
        throw std::runtime_error(oss.str());
      }
    }

    return final_result + cur_result;
  }

  int GetOneNumber(const std::string &expression, std::size_t &idx) {
    SkipSpace(expression, idx);
    auto got_unary_minus = false;
    if (expression[idx] == '-') {
      got_unary_minus = true;
      idx++;
    }
    if (expression[idx] == '(') {
      idx++;
      return Calculate(expression, idx);
    }

    assert(std::isdigit(expression[idx]));
    auto result{0};
    while (std::isdigit(expression[idx])) {
      result = result * 10 + expression[idx] - '0';
      idx++;
    }
    return got_unary_minus ? -result : result;
  }

  void SkipSpace(const std::string &expression, std::size_t &idx) {
    while (idx < expression.length() && std::isspace(expression[idx])) {
      idx++;
    }
  }

public:
  // https://www.lintcode.com/problem/849
  // With all binary operators (+, -, * and /), brackets and unary operator - taken into consideration
  int calculate(const std::string &expression) {
    auto idx{static_cast<std::size_t>(0)};
    auto result = Calculate(expression, idx);
    assert(idx == expression.length());

    return result;
  }
};

int main() {
  auto sol{Solution()};
  assert(23 == sol.calculate("(1+(4+5+2)-3)+(6+8)"));
  assert(4 == sol.calculate("1+ 3"));
  assert(-3 == sol.calculate("-1 - 2"));
  assert(53 == sol.calculate("(1 + (2 -3 + -4) * -5 / -6 - 7* -8)"));
}