#include <unordered_set>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void permutations_helper(const std::vector<int> &A, std::vector<int> &curr_perm,
                         std::vector<std::vector<int>> &result,
                         std::unordered_set<int> used_indices) {
  if (used_indices.size() == A.size()) {
    result.push_back(curr_perm);
    return;
  }
  for (auto i{0}; i < A.size(); ++i) {
    if (!used_indices.count(i)) {
      auto new_used_indices = used_indices;
      auto new_perm = curr_perm;
      new_perm.push_back(A[i]);
      new_used_indices.insert(i);
      permutations_helper(A, new_perm, result, new_used_indices);
    }
  }
}

vector<vector<int>> Permutations(vector<int> A) {
  std::vector<std::vector<int>> result{};
  std::vector<int> start_perm{};
  std::unordered_set<int> used_indices{};
  permutations_helper(A, start_perm, result, used_indices);
  return result;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "permutations.cc", "permutations.tsv",
                         &Permutations, UnorderedComparator{}, param_names);
}
