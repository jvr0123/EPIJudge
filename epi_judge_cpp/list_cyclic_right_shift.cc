#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> CyclicallyRightShiftList(shared_ptr<ListNode<int>> L, int k) {
    auto oldHead{L}, curr{L};
    auto listLen{0};
    if (!L) {
        return L;
    }
    while (curr != nullptr) {
        curr = curr->next;
        ++listLen;
    }
    curr = oldHead;
    k %= listLen;
    if (k == 0) {
        return oldHead;
    }
    for (auto idx{0}; idx < listLen - k - 1; ++idx) {
        curr = curr->next;
    }
    auto newHead = curr->next;
    curr->next = nullptr;
    curr = newHead;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = oldHead;
    return newHead;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"L", "k"};
    return GenericTestMain(args,
                           "list_cyclic_right_shift.cc",
                           "list_cyclic_right_shift.tsv",
                           &CyclicallyRightShiftList,
                           DefaultComparator{},
                           param_names);
}
