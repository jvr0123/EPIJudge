#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

struct heightBalance{
  int height{};
  bool balance{true};
};

heightBalance depth(const unique_ptr<BinaryTreeNode<int>>& tree){
  if(!tree)
    return {0, true};
  auto left = depth(tree->left);
  auto right = depth(tree->right); 
  return {std::max(left.height, right.height) + 1, left.balance && right.balance && std::abs(left.height - right.height) <= 1};
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return depth(tree).balance; 
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
