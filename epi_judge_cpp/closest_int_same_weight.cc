#include "test_framework/generic_test.h"
unsigned long long ClosestIntSameBitCount(unsigned long long x) {
  int kUnsignedBits = 64; //size of uLL
  for (int i = 0; i <= kUnsignedBits - 1; ++i)
  {
    //check for the two consecutive rightmost bits which are unequal
    if ((((x >> i) & 1)) != (((x >> (i + 1) & 1)))){
      x ^= (1ULL << i) | (1ULL << (i+1)); // swap them
      return x;
    }
  }
  return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "closest_int_same_weight.cc",
                         "closest_int_same_weight.tsv", &ClosestIntSameBitCount,
                         DefaultComparator{}, param_names);
}
