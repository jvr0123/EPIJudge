#include <iterator>
#include <vector>
#include <algorithm>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> ExamineBuildingsWithSunset(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end) {
  std::vector<std::pair<int, int>> monoStack{};
  std::vector<int> res{};
  auto buildingIdx{0};
  while(sequence_begin != sequence_end){
    while(!monoStack.empty() && *sequence_begin >= monoStack.back().second){
      monoStack.pop_back();
    }
    monoStack.push_back(std::make_pair(buildingIdx, *sequence_begin));
    ++sequence_begin, ++buildingIdx;
  }
  for(const auto& pa : monoStack){
    res.emplace_back(pa.first);
  }
  std::reverse(res.begin(), res.end());
  return res;
}
vector<int> ExamineBuildingsWithSunsetWrapper(const vector<int>& sequence) {
  return ExamineBuildingsWithSunset(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "sunset_view.cc", "sunset_view.tsv",
                         &ExamineBuildingsWithSunsetWrapper,
                         DefaultComparator{}, param_names);
}
