#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
#include <set>

int getDepth(const unique_ptr<BinaryTreeNode<int>> &node) {
  auto head = node.get();
  auto depth{0};
  while (head != nullptr) {
    ++depth;
    head = head->parent;
  }
  return depth;
}

void advanceNode(BinaryTreeNode<int> *&node, int n) {
  while (n) {
    node = node->parent;
    --n;
  }
}

BinaryTreeNode<int> *Lca(const unique_ptr<BinaryTreeNode<int>> &node0,
                         const unique_ptr<BinaryTreeNode<int>> &node1) {
  auto d0 = getDepth(node0), d1 = getDepth(node1);
  auto parent0 = node0.get(), parent1 = node1.get();
  if(d0 > d1){
    advanceNode(parent0, d0 - d1);
  }
  else{
    advanceNode(parent1, d1 - d0);
  }
  while(parent1 != nullptr && parent0 != nullptr){
    if(parent1 == parent0)
      return parent1;
    parent1 = parent1->parent, parent0 = parent0->parent;
  }
  return nullptr;
}
int LcaWrapper(TimedExecutor &executor,
               const unique_ptr<BinaryTreeNode<int>> &tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>> &node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>> &node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
