#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> AddTwoNumbers(shared_ptr<ListNode<int>> L1, shared_ptr<ListNode<int>> L2) {
    shared_ptr<ListNode<int>> sum{new ListNode<int>};
    auto sumIter = sum;
    auto carry{0};
    while (L1 || L2 || carry) {
        carry += (L1 ? L1->data : 0) + (L2 ? L2->data : 0);
        L1 = L1 ? L1->next : L1;
        L2 = L2 ? L2->next : L2;
        if (carry >= 10) {
            sumIter->next = make_shared<ListNode<int>>(carry % 10);
            carry /= 10;
        } else {
            sumIter->next = make_shared<ListNode<int>>(carry);
            carry = 0;
        }
        sumIter = sumIter->next;
    }
    return sum->next;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"L1", "L2"};
    return GenericTestMain(args,
                           "int_as_list_add.cc",
                           "int_as_list_add.tsv",
                           &AddTwoNumbers,
                           DefaultComparator{},
                           param_names);
}
