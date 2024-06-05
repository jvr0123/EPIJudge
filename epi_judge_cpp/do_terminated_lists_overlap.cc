#include <memory>
#include <set>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

int list_length(shared_ptr<ListNode<int>> list)
{
  auto len {0};
  auto curr {list};
  while(curr){
    ++len;
    curr = curr->next;
  }
  return len;
}

void advance_list_by_k(int k, shared_ptr<ListNode<int>>* list){
  while(k)
  {
    *list = (*list)->next;
    --k;
  }
}

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
    shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
  auto len0{list_length(l0)}, len1{list_length(l1)};
  advance_list_by_k(abs(len1 - len0), len1 > len0 ? &l1 : &l0);
  while(l1 && l0){
    if(l1 == l0) {
      return l0;
    }
    l1 = l1->next;
    l0 = l0->next;    
  }
  return nullptr;
}

void OverlappingNoCycleListsWrapper(TimedExecutor& executor,
                                    shared_ptr<ListNode<int>> l0,
                                    shared_ptr<ListNode<int>> l1,
                                    shared_ptr<ListNode<int>> common) {
  if (common) {
    if (l0) {
      auto i = l0;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l0 = common;
    }

    if (l1) {
      auto i = l1;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l1 = common;
    }
  }

  auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

  if (result != common) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0", "l1", "common"};
  return GenericTestMain(
      args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
      &OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}
