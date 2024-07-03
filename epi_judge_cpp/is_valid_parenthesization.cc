#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsWellFormed(const string& s) {
    std::stack<char> leftChars{};
    const std::unordered_map<char, char> parenthesis{{'(', ')'}, {'[', ']'}, {'{', '}'}};
    for (const auto& c : s) {
        if (parenthesis.count(c))
            leftChars.emplace(c);
        else {
            if (leftChars.empty() || parenthesis.at(leftChars.top()) != c) {
                return false;
            }
            leftChars.pop();
        }
    }
    return leftChars.empty();
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"s"};
    return GenericTestMain(args,
                           "is_valid_parenthesization.cc",
                           "is_valid_parenthesization.tsv",
                           &IsWellFormed,
                           DefaultComparator{},
                           param_names);
}
