#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> reverseList(shared_ptr<ListNode<int>> head) {
    shared_ptr<ListNode<int>> prev{nullptr}, next{nullptr};
    auto curr{head};
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L) {
    if (!L)
        return true;
    auto slow{L}, fast{L};
    while(fast && fast ->next){
      slow = slow -> next;
      fast = fast->next->next;
    }
    auto reverse{reverseList(slow)};
    while (reverse && L && L != reverse) {
        if (reverse->data != L->data)
            return false;
        reverse = reverse->next, L = L->next;
    }
    return true;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"L"};
    return GenericTestMain(args,
                           "is_list_palindromic.cc",
                           "is_list_palindromic.tsv",
                           &IsLinkedListAPalindrome,
                           DefaultComparator{},
                           param_names);
}
