#include <atomic>
#include <functional>
#include <thread>
#include "src/common/queue.h"

namespace common {

using Task = std::function<void()>;
class ThreadPool {
 public:
  ThreadPool (size_t size = 0) : exit_(false) {
    if (size = 0) size = std::thread::hardware_concurrency();
    for (size_t i = 0; i < size; ++i) {
      threads_.emplace_back(std::thread(&ThreadPool::worker_thread, this));
    }
  }
  ~ThreadPool() {
    exit_ = true;
  }
  template<typename FunctionType>
  void submit(FunctionType f)
  {
    work_queue.push(std::function<void()>(f));  // 12
  }
  void worker_thread()
  {
    while(!exit_)  // 4
    {
      Task task;
      if(work_queue_.try_pop(task))  // 5
      {
        task();  // 6
      }
      else
      {
        std::this_thread::yield();  // 7
      }
    }
  }

 protected:
  std::atomic_bool exit_;
  Queue<std::function<void()> > work_queue_;  // 1
  std::vector<std::thread> threads_;  // 2
};

}  // namespace common