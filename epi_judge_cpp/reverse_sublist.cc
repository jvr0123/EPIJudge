#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  if (!L || !L->next)
    return L;
  auto curr = L;
  shared_ptr<ListNode<int>> start_splice{nullptr}, end_splice{nullptr};
  auto idx{1};
  while (curr) {
    if (idx == start - 1) {
      start_splice = curr;
    } else if (idx == finish + 1) {
      end_splice = curr;
    }
    ++idx;
    curr = curr->next;
  }
  if (start_splice)
    curr = start_splice->next;
  else
    curr = L;
  auto prev = end_splice;
  auto next = curr->next;
  while (curr != end_splice) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  if(start_splice)
  {
    start_splice->next = prev;
    return L;
  }
  return prev;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
