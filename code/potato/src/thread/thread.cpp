#include <cassert>
#include <pthread.h>

#include "thread.h"

namespace ac{
namespace thread{

void *DoWork(void* pData)
{
  /// force to cast
  IWorker* worker_ptr = reinterpret_cast<IWorker*>(pData);
  worker_ptr->Do();

  /// terminate the thread
  pthread_exit(NULL);
}

void DoJob(thread::IWorker* pWorkers[], const int& riCount)
{
  void* status_ptr;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  /// allocate the memory of thread array
  pthread_t* threads = new pthread_t[riCount];

  int i = 0;
  for (i = 0; i < riCount; ++i)
  {
    assert(0 == pthread_create(&threads[i], &attr, DoWork, (void*)pWorkers[i]));
  }

  pthread_attr_destroy(&attr);

  for (i = 0; i < riCount; ++i)
  {
    pthread_join(threads[i], &status_ptr);
  }

  /// free the memory of thread array
  delete[] threads;

  /// terminate the thread
  pthread_exit(NULL);
}

} // end of namespace thread
} // end of namespace ac
