#include <stdexcept>
#include <list>
#include <map>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
using std::length_error;

class QueueWithMax
{
public:
  void Enqueue(int x)
  {
    mQueue.emplace_back(x);
    ++mMaxMap[x];
    return;
  }
  int Dequeue()
  {
    auto top = mQueue.front();
    mQueue.pop_front();
    if (mMaxMap[top] == 1)
      mMaxMap.erase(top);
    else
      --mMaxMap[top];
    return top;
  }
  int Max() const
  {
    return (*mMaxMap.crbegin()).first;
  }

private:
  std::map<int, int> mMaxMap{};
  std::list<int> mQueue{};
};
struct QueueOp
{
  enum class Operation
  {
    kConstruct,
    kDequeue,
    kEnqueue,
    kMax
  } op;
  int argument;

  QueueOp(const std::string &op_string, int arg) : argument(arg)
  {
    if (op_string == "QueueWithMax")
    {
      op = Operation::kConstruct;
    }
    else if (op_string == "dequeue")
    {
      op = Operation::kDequeue;
    }
    else if (op_string == "enqueue")
    {
      op = Operation::kEnqueue;
    }
    else if (op_string == "max")
    {
      op = Operation::kMax;
    }
    else
    {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }
};

namespace test_framework
{
  template <>
  struct SerializationTrait<QueueOp> : UserSerTrait<QueueOp, std::string, int>
  {
  };
} // namespace test_framework

void QueueTester(const std::vector<QueueOp> &ops)
{
  try
  {
    QueueWithMax q;
    for (auto &x : ops)
    {
      switch (x.op)
      {
      case QueueOp::Operation::kConstruct:
        break;
      case QueueOp::Operation::kDequeue:
      {
        int result = q.Dequeue();
        if (result != x.argument)
        {
          throw TestFailure("Dequeue: expected " +
                            std::to_string(x.argument) + ", got " +
                            std::to_string(result));
        }
      }
      break;
      case QueueOp::Operation::kEnqueue:
        q.Enqueue(x.argument);
        break;
      case QueueOp::Operation::kMax:
      {
        int s = q.Max();
        if (s != x.argument)
        {
          throw TestFailure("Max: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(s));
        }
      }
      break;
      }
    }
  }
  catch (const length_error &)
  {
    throw TestFailure("Unexpected length_error exception");
  }
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "queue_with_max.cc", "queue_with_max.tsv",
                         &QueueTester, DefaultComparator{}, param_names);
}
