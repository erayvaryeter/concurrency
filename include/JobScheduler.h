#pragma once

#include <chrono>
#include "Worker.h"

class JobScheduler {
public:
    JobScheduler(int numWorkers);
    ~JobScheduler();

    void start();
    void stop();
    void addJob(const Job& job);
    int getJobCounter() const;
    std::chrono::steady_clock::time_point getLastTimePoint();

private:
    Semaphore m_semaphore;
    std::queue<Job> m_jobs;
    std::mutex m_queueMutex;
    std::vector<Worker> m_workers;
    std::atomic<int> m_jobCounter;
    std::chrono::steady_clock::time_point m_lastTimePoint;
};