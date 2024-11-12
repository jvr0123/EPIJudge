#include <memory>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

struct Ancestry
{
  int numChildren{};
  BinaryTreeNode<int> *ancestor;
};

Ancestry LcaHelper(const unique_ptr<BinaryTreeNode<int>> &tree,
                   const unique_ptr<BinaryTreeNode<int>> &node0,
                   const unique_ptr<BinaryTreeNode<int>> &node1)
{
  if (tree == nullptr)
  {
    return {0, nullptr};
  }

  auto left{LcaHelper(tree->left, node0, node1)};
  if (left.numChildren == 2)
    return left;

  auto right{LcaHelper(tree->right, node0, node1)};
  if (right.numChildren == 2)
    return right;
  
  auto numChildren = left.numChildren + right.numChildren + (tree == node0) + (tree == node1);
  return {numChildren, numChildren == 2 ? tree.get() : nullptr};
}

BinaryTreeNode<int> *Lca(const unique_ptr<BinaryTreeNode<int>> &tree,
                         const unique_ptr<BinaryTreeNode<int>> &node0,
                         const unique_ptr<BinaryTreeNode<int>> &node1)
{
  return LcaHelper(tree, node0, node1).ancestor;
}
int LcaWrapper(TimedExecutor &executor,
               const unique_ptr<BinaryTreeNode<int>> &tree, int key0,
               int key1)
{
  const unique_ptr<BinaryTreeNode<int>> &node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>> &node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&]
                             { return Lca(tree, node0, node1); });

  if (!result)
  {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
