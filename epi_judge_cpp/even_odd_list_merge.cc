#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
    auto dummyEvens{make_shared<ListNode<int>>(ListNode<int>{0, nullptr})},
        dummyOdds{make_shared<ListNode<int>>(ListNode<int>{0, nullptr})};
    std::array<shared_ptr<ListNode<int>>, 2>currLists{dummyEvens, dummyOdds};
    auto parity{0};
    for (auto curr{L}; curr != nullptr; curr = curr->next) {
        currLists[parity]->next = curr;
        currLists[parity] = currLists[parity]->next;
        parity ^= 1;
    }
    currLists[1]->next = nullptr;
    currLists[0]->next = dummyOdds->next;
    return dummyEvens->next;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"L"};
    return GenericTestMain(args,
                           "even_odd_list_merge.cc",
                           "even_odd_list_merge.tsv",
                           &EvenOddMerge,
                           DefaultComparator{},
                           param_names);
}
