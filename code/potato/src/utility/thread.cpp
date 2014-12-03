/*!
 * \file thread.cpp
 * \brief the implement for the thread.h file
 */
#include <cassert>
//#include <pthread.h>

#include "thread.h"

namespace c4g {
namespace thread {

void* DoWorkFunc(void* pData)
{
  /*assert(NULL != pData);

  /// force to cast
  IWorker* worker_ptr = reinterpret_cast<IWorker*>(pData);
  worker_ptr->Do();

  /// terminate the thread
  pthread_exit(NULL);*/
  return nullptr;
}

void DoJob(thread::IWorker* pWorkers[], const int& riCount)
{
  /*if (0 >= riCount)
  {
    return;
  }

  void* status_ptr;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  /// allocate the memory of thread array
  pthread_t* threads = new pthread_t[riCount];

  int i = 0;

  /// create a thread for every workers
  for (i = 0; i < riCount; ++i)
  {
    assert(0 == pthread_create(&threads[i], &attr, DoWorkFunc, (void* )pWorkers[i]));
  }

  pthread_attr_destroy(&attr);

  /// run all threads
  for (i = 0; i < riCount; ++i)
  {
    pthread_join(threads[i], &status_ptr);
  }

  /// free the memory of thread array
  delete[] threads;*/

  /// terminate the thread
  //pthread_exit(NULL);
}

} // end of namespace thread
} // end of namespace ac
