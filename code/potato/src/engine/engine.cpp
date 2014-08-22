#include "engine.h"

#include "util_log.h"
#include "thread.h"

#include <cassert>
#include <unistd.h>
#include <iostream>

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
    std::cout << "do render work" << std::endl;

    int i = 0;
    while (Status)
    {
      std::cout << i++ << std::endl;
      sleep(1);
    }
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
    std::cout << "do net work" << std::endl;
    sleep(5);
    m_pRenderWorker->Status = 0;
  }

private:
  RendWorker* m_pRenderWorker;
};

class EngineWorker : public thread::IWorker
{
public:
  EngineWorker() { ; }
  virtual ~EngineWorker() { ; }

public:
  virtual void Do()
  {
    std::cout << "do work" << std::endl;
    RendWorker render_worker;
    NetWorker net_worker;
    net_worker.SetRenderWorker(&render_worker);
    thread::IWorker* workers[] = {&render_worker, &net_worker};
    thread::DoJob(workers, 2);
  }
};

void CEngine::Run()
{
  utility::Log::Instance().System("engine is running");

  EngineWorker worker;
  thread::IWorker* workers[] = {&worker};
  thread::DoJob(workers, 1);
}

}
}
