#include <cassert>
#include <unistd.h>
#include <iostream>

#include "engine.h"
#include "thread.h"
#include "util_log.h"

bool CreateEngine(ac::core::IEngine*& rpEngine, const ac::base::Config& roConfig)
{
  assert(rpEngine == NULL);
  rpEngine = new ac::core::CEngine(roConfig);
  return true;
}

bool DestroyEngine(ac::core::IEngine*& rpEngine, const ac::base::Config& roConfig)
{
  assert(rpEngine != NULL);
  delete rpEngine;
  rpEngine = NULL;
  return true;
}

namespace ac{
namespace core{

CEngine::CEngine(const ac::base::Config& roConfig)
{
  utility::Log::Instance().System("call the 'CEngine' constructor");
}

CEngine::~CEngine()
{
  utility::Log::Instance().System("call the 'CEngine' destructor");
}

class RendWorker : public thread::IWorker
{
public:
  RendWorker()
    : Status(1)
  {
    ;
  }
  virtual ~RendWorker() { ; }

  virtual void Do()
  {
    utility::Log::Instance().System("start the render work");

    int i = 0;
    while (Status)
    {
      utility::Log::Instance().System("%d the render worker", i++);
      //std::cout << "second is " << i++ << std::endl;
      sleep(1);
    }
    utility::Log::Instance().System("end the render work");
  }
  volatile int Status;
};

class NetWorker : public thread::IWorker
{
public:
  void SetRenderWorker(RendWorker* pWorker)
  {
    m_pRenderWorker = pWorker;
  }

  virtual void Do()
  {
    utility::Log::Instance().System("start the net work");
    int i = 0;
    while (1)
    {
      utility::Log::Instance().System("%d the net worker", i++);
      //std::cout << "second is " << i++ << std::endl;
      sleep(1);
      if (5 == i)
      {
        break;
      }
    }
    m_pRenderWorker->Status = 0;
    utility::Log::Instance().System("end the net work");
  }

private:
  RendWorker* m_pRenderWorker;
};

void CEngine::Run()
{
  utility::Log::Instance().TestAllLogTypes();
  utility::Log::Instance().System("engine is running");

  RendWorker render_worker;
  NetWorker net_worker;
  net_worker.SetRenderWorker(&render_worker);
  thread::IWorker* workers[] = {&render_worker, &net_worker};
  thread::DoJob(workers, 2);
}

}
}
