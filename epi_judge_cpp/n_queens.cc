#include <algorithm>
#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;:

bool is_valid(const std::vector<int> &col_placement) {
  int row = col_placement.size() - 1;
  for (auto i{0}; i < row; ++i) {
    auto diff = std::abs(col_placement[i] - col_placement[row]);
    if (diff == 0 || diff == row - i)
      return false;
  }
  return true;
}

void place_queens(int row, int n, std::vector<int> *col_placement,
                  std::vector<std::vector<int>> &board) {
  if (row == n) {
    board.push_back(*col_placement);
  } else {
    for (auto i{0}; i < n; ++i) {
      col_placement->emplace_back(i);
      if (is_valid(*col_placement)) {
        place_queens(row + 1, n, col_placement, board);
      }
      col_placement->pop_back();
    }
  }
}

vector<vector<int>> NQueens(int n) {
  std::vector<std::vector<int>> board{};
  place_queens(0, n, std::make_unique<std::vector<int>>().get(), board);
  return board;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens,
                         UnorderedComparator{}, param_names);
}
