#pragma once

namespace ac {

namespace thread {

class ITask
{
public:
  virtual ~ITask() { ; }

public:
  virtual void Tick(const float& rfDeltaS) = 0;
};

class IWorker
{
public:
  virtual ~IWorker() { ; }

public:
  virtual void Do() = 0;
};

void DoJob(thread::IWorker* pWorkers[], const int& riCount);

} // end of namespace thread
} // end of namespace ac
