/*!
 * \file thread.h
 * \brief a common thread toolkits
 */
#pragma once

namespace ac {
namespace thread {

/*!
 * \class ITask
 * \brief the task of a worker
 */
class ITask
{
public:
  virtual ~ITask() { ; }

public:
  virtual void Ready() = 0;
  virtual void Start() = 0;
  /*!
   * \func Run(const float& rfDeltaS)
   * \param rfDeltaS the delta time in second
   */
  virtual void Run(const float& rfDeltaS) = 0;
  virtual void Stop() = 0;
};

/*!
 * \class IWorker
 * \brief the worker will have a thread
 *
 * it will be called to do some tasks by a thread
 */
class IWorker
{
public:
  virtual ~IWorker() { ; }

public:
  /*!
   * \func Do()
   *
   * do the task, is assigned
   */
  virtual void Do() = 0;
};

/*!
 * \function DoJob(thread::IWorker* pWorkers[], const int& riCount)
 *
 * create a thread for every workers
 */
void DoJob(thread::IWorker* pWorkers[], const int& riCount);

} // end of namespace thread
} // end of namespace ac
