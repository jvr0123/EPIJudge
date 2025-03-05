#include <array>
#include <stack>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::array;
using std::stack;
using std::vector;
const int kNumPegs = 3;
void hanoi_helper(int num_rings_left, int from_ring, int to_ring, int swap_ring,
                  std::array<std::stack<int>, kNumPegs> &state,
                  vector<vector<int>> &moves) {
  if (num_rings_left) {
    hanoi_helper(num_rings_left - 1, from_ring, swap_ring, to_ring, state,
                 moves);
    state[to_ring].push(state[from_ring].top());
    state[from_ring].pop();
    moves.emplace_back(std::vector<int>{from_ring, to_ring});
    hanoi_helper(num_rings_left - 1, swap_ring, to_ring, from_ring, state,
                 moves);
  }
}
vector<vector<int>> ComputeTowerHanoi(int num_rings) {
  std::array<std::stack<int>, kNumPegs> rings{};
  for (int i{0}; i < num_rings; ++i) {
    rings[0].push(i);
  }
  std::vector<vector<int>> moves{};
  hanoi_helper(num_rings, 0, 1, 2, rings, moves);
  return moves;
}
void ComputeTowerHanoiWrapper(TimedExecutor &executor, int num_rings) {
  array<stack<int>, kNumPegs> pegs;
  for (int i = num_rings; i >= 1; --i) {
    pegs[0].push(i);
  }

  vector<vector<int>> result =
      executor.Run([&] { return ComputeTowerHanoi(num_rings); });

  for (const vector<int> &operation : result) {
    int from_peg = operation[0], to_peg = operation[1];
    if (!pegs[to_peg].empty() && pegs[from_peg].top() >= pegs[to_peg].top()) {
      throw TestFailure("Illegal move from " +
                        std::to_string(pegs[from_peg].top()) + " to " +
                        std::to_string(pegs[to_peg].top()));
    }
    pegs[to_peg].push(pegs[from_peg].top());
    pegs[from_peg].pop();
  }
  array<stack<int>, kNumPegs> expected_pegs1, expected_pegs2;
  for (int i = num_rings; i >= 1; --i) {
    expected_pegs1[1].push(i);
  }
  for (int i = num_rings; i >= 1; --i) {
    expected_pegs2[2].push(i);
  }
  if (pegs != expected_pegs1 && pegs != expected_pegs2) {
    throw TestFailure("Pegs doesn't place in the right configuration");
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "num_rings"};
  return GenericTestMain(args, "hanoi.cc", "hanoi.tsv",
                         &ComputeTowerHanoiWrapper, DefaultComparator{},
                         param_names);
}
