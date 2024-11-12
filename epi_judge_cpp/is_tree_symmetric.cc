#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool CheckSymmetry(const unique_ptr<BinaryTreeNode<int>>& ltree, const unique_ptr<BinaryTreeNode<int>>& rtree){
  if(ltree == nullptr && rtree == nullptr)
    return true;
  else if(ltree == nullptr || rtree == nullptr || ltree->data != rtree->data){
    return false;
  }
  else{
    return CheckSymmetry(ltree->right, rtree->left) && CheckSymmetry(ltree->left, rtree->right);
  }
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return tree == nullptr || CheckSymmetry(tree->left, tree->right);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
