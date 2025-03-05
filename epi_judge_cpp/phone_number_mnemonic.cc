#include "test_framework/generic_test.h"
#include <string>
#include <unordered_map>
#include <vector>
using std::string;
using std::vector;

static const std::unordered_map<int, std::vector<char>> k_keypad_map{
    {0, {'0'}},           {1, {'1'}},
    {2, {'A', 'B', 'C'}}, {3, {'D', 'E', 'F'}},
    {4, {'G', 'H', 'I'}}, {5, {'J', 'K', 'L'}},
    {6, {'M', 'N', 'O'}}, {7, {'P', 'Q', 'R', 'S'}},
    {8, {'T', 'U', 'V'}}, {9, {'W', 'X', 'Y', 'Z'}}};
void phone_helper(const std::string &phone_number, int index,
                  std::string curr_mnemonic, std::vector<string> &mnemonics) {
  if (index == phone_number.size()) {
    mnemonics.push_back(curr_mnemonic);
    return;
  }
  auto num = static_cast<int>(phone_number[index] - '0');
  for (const auto &c : k_keypad_map.at(num)) {
    phone_helper(phone_number, index + 1, curr_mnemonic + c, mnemonics);
  }
}
vector<string> PhoneMnemonic(const string &phone_number) {
  std::vector<std::string> mnemonics{};
  phone_helper(phone_number, 0, "", mnemonics);
  return mnemonics;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"phone_number"};
  return GenericTestMain(args, "phone_number_mnemonic.cc",
                         "phone_number_mnemonic.tsv", &PhoneMnemonic,
                         UnorderedComparator{}, param_names);
}
