#include <string>

#include "test_framework/generic_test.h"
using std::string;
int Evaluate(const string& expression) {
    std::stack<int> results{};
    std::stringstream ss{expression};
    const char delimiter{','};
    std::string token;
    const std::unordered_map<std::string, std::function<int(int, int)>> operators{ 
      {"+", [](int x, int y) -> int {return x + y;}},
      {"-", [](int x, int y) -> int {return x - y;}},
      {"*", [](int x, int y) -> int {return x * y;}},
      {"/", [](int x, int y) -> int {return x / y;}}
    };
    while(std::getline(ss, token, delimiter)){
      if(operators.count(token)){
        const int y = results.top();
        results.pop();
        const int x = results.top();
        results.pop();
        results.push(operators.at(token)(x, y));
      }
      else{
        results.push(std::stoi(token));
      }

    }
    return results.top();
    
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"expression"};
    return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate, DefaultComparator{}, param_names);
}
