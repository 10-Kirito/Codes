#include <iostream>
#include <future>
#include <chrono>
#include <thread>

int async_operation(const std::string & task_name, int seconds){
    std::cout << "Start " << task_name << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    std::cout << "End " << task_name << std::endl;
    return seconds * 100;
}

int main() {
    std::future<int> result1 = std::async(std::launch::async, async_operation, "Task 1", 2);
    std::future<int> result2 = std::async(std::launch::async, async_operation, "Task 2", 1);
    std::future<int> result3 = std::async(std::launch::async, async_operation, "Task 3", 3);

    // do something in the main thread:
    std::cout << "Main thread working..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Main thread still working..." << std::endl;

    int value1 = result1.get();
    int value2 = result2.get();
    int value3 = result3.get();

    std::cout << "Final result: " << (value1 + value2 + value3) << std::endl;

    return 0;
}