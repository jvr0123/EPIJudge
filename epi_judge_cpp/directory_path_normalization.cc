#include <string>
#include <vector>
#include <sstream>

#include "test_framework/generic_test.h"
using std::string;
string ShortestEquivalentPath(const string &path)
{
  std::vector<string> path_names{};
  if (path.front() == '/')
  {
    path_names.emplace_back("/");
  }

  std::stringstream ss(path);
  string token{};

  while (getline(ss, token, '/'))
  {
    if (token == "..")
    {
      if (empty(path_names) || path_names.back() == "..")
      {
        path_names.emplace_back(token);
      }
      else
      {
        path_names.pop_back();
      }
    }
    else if (token != "." && token != "")
    {
      path_names.emplace_back(token);
    }
  }
  std::string result{};
  if (!empty(path_names))
  {
    result = path_names.front();
    for (auto i{1}; i < path_names.size(); ++i)
    {
      if (i == 1 && result == "/")
      {
        result += path_names[i];
      }
      else
      {
        result += "/" + path_names[i];
      }
    }
  }
  return result;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"path"};
  return GenericTestMain(args, "directory_path_normalization.cc",
                         "directory_path_normalization.tsv",
                         &ShortestEquivalentPath, DefaultComparator{},
                         param_names);
}
