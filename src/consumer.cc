#include <atomic>
#include <iostream>
#include <memory>
#include <thread>
#include <cstdlib>
#include <unistd.h>

#include "src/common/queue.h"

std::mutex m;

struct PersonData {
  std::string name;
  size_t age;
};

static PersonData GetData() {
  srand((unsigned long)time(NULL));
  PersonData data;
  data.name = "test";
  data.age = rand() % 100;
  return data;
}

static void PrintData(const std::string& prefix,
                      const PersonData& person_data) {
  std::lock_guard<std::mutex> lck (m);
  std::cout << prefix << std::endl;
  std::cout << "Name : " << person_data.name << std::endl;
  std::cout << "Age : " << person_data.age << std::endl;
}

void Producer(std::shared_ptr<common::Queue<PersonData>> queue) {
  while(true) {
    auto data = GetData();
    queue->push(data);
    PrintData("Producer", data);
    sleep(1);
  }
}
void Comsumer(std::shared_ptr<common::Queue<PersonData>> queue) {
  while(true) {
    auto data = queue->wait_and_pop();
    PrintData("Consumer", *data.get());   
    sleep(2);
  }
}

int main() {
  std::shared_ptr<common::Queue<PersonData>> queue(new common::Queue<PersonData>());
  std::thread producer_thread(Producer, queue);
  std::thread consumer_thread(Comsumer, queue);
  
  producer_thread.join();
  consumer_thread.join();
  std::cout << "by likewind1993" << std::endl;
  return 0;
}