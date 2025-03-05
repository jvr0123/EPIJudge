#include <memory>
#include <stack>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>> &tree) {
  std::vector<int> inorder_vector{};
  std::stack<BinaryTreeNode<int> *> node_stack{};
  auto curr = tree.get();
  while (!node_stack.empty() || curr) {
    while (curr) {
      node_stack.push(curr);
      curr = curr->left.get();
    }
    curr = node_stack.top();
    node_stack.pop();
    inorder_vector.push_back(curr->data);
    curr = curr->right.get();
  }
  return inorder_vector;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
