#include <atomic>
#include <condition_variable>
#include <memory>
#include <queue>

// thread safe 
// with mutex lock

namespace common {

template <typename T>
class Queue {
 public:
  Queue() = default;
  Queue(const Queue&) = default;
  Queue& operator=(const Queue&) = delete; // 禁止简单赋值赋值
  
  size_t size() const {
    std::lock_guard<std::mutex> lck(m_);
    return queue_.size();
  };
  bool empty() const {
    std::lock_guard<std::mutex> lck(m_);
    return queue_.empty();
  };

  T& front() {
    std::lock_guard<std::mutex> lck(m_);
    return queue_.front();
  }
  const T& front() const {
    std::lock_guard<std::mutex> lck(m_);
    return queue_.front();
  };
  T& back() {
    std::lock_guard<std::mutex> lck(m_);
    return queue_.back();
  }
  const T& back() const{
    std::lock_guard<std::mutex> lck(m_);
    return queue_.back();
  }
  bool try_pop(T& value) {
    std::lock_guard<std::mutex> lck(m_);
    if (queue_.empty()) return false;
    value = queue_.front();
    queue_.pop();
  }
  void wait_and_pop(T& value) {
    std::unique_lock<std::mutex> lck(m_);
    cond_.wait(lck, [this]{ return !queue_.empty(); });
    value = queue_.front();
    queue_.pop();
  }
  std::shared_ptr<T> wait_and_pop() {
    std::unique_lock<std::mutex> lck(m_);
    cond_.wait(lck, [this]{ return !queue_.empty(); });
    std::shared_ptr<T> res(std::make_shared<T>(queue_.front()));
    queue_.pop();
    return res;
  }

  void push(const T& x) {
    std::lock_guard<std::mutex> lck(m_);
    queue_.push(x);
    cond_.notify_one();
  }
  void push(T&& x) {
    std::lock_guard<std::mutex> lck(m_);
    queue_.push(std::move(x));
    cond_.notify_one();
  }
  void pop() {
    std::lock_guard<std::mutex> lck(m_);
    queue_.pop();
  }
  template <class... Args> void emplace(Args&&... args);

 private:
  std::queue<T> queue_;
  std::mutex m_;
  std::condition_variable cond_;
};

}  // namespace common