#pragma once

#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>

struct Job {
    int jobID = 0;
    std::string jobName;
    int jobDurationMs = 0;
};

class Semaphore {
public:
    Semaphore(int count = 0) : m_count(count) {}

    void notify();
    void wait();

private:
    std::mutex m_mutex;
    std::condition_variable m_condition;
    int m_count = 0;
};