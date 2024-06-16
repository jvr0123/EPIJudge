#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  if(!L1)
    return L2;
  if(!L2)
    return L1;
  shared_ptr<ListNode<int>> curr = L1->data < L2->data ? L1 : L2;
  shared_ptr<ListNode<int>> other = L1 == curr ? L2 : L1;
  shared_ptr<ListNode<int>> ret = curr;
  while (curr->next && other) {
    if (other->data < curr->next->data) {
      auto temp_curr = curr->next;
      auto temp_other = other->next;
      curr->next = other;
      curr->next->next = temp_curr;
      other = temp_other;
    }
    curr = curr->next;
  }

  if(other) {
    curr->next = other;
  }

  return ret;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
