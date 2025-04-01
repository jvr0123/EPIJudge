#include "test_framework/generic_test.h"
#include <math.h>
#include <vector>
using std::vector;

vector<vector<int>> GeneratePowerSet(const vector<int> &input_set) {
  std::vector<std::vector<int>> power_set{std::vector<int>{}};
  for (const auto &elem : input_set) {
    std::vector<std::vector<int>> add_sets{};
    for (auto subset : power_set) {
      subset.push_back(elem);
      add_sets.push_back(subset);
    }
    for (const auto &set : add_sets) {
      power_set.push_back(set);
    }
  }
  return power_set;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"input_set"};
  return GenericTestMain(args, "power_set.cc", "power_set.tsv",
                         &GeneratePowerSet, UnorderedComparator{}, param_names);
}
