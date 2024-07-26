#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>> &tree)
{
  std::vector<vector<int>> res{};
  if (!tree)
    return res;
  std::queue<BinaryTreeNode<int> *> currLevel{};
  currLevel.emplace(tree.get());
  while (!currLevel.empty())
  {
    std::vector<int> level{};
    std::queue<BinaryTreeNode<int> *> nextLevel{};
    while (!currLevel.empty())
    {
      auto curr = currLevel.front();
      currLevel.pop();
      level.emplace_back(curr->data);
      if (curr->left)
        nextLevel.emplace(curr->left.get());
      if (curr->right)
        nextLevel.emplace(curr->right.get());
    }
    res.emplace_back(level);
    currLevel = nextLevel;
  }

  return res;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
