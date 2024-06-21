#pragma once

#include <queue>
#include <atomic>
#include "Semaphore.h"

class Worker {
public:
    Worker(int id, Semaphore& sem, std::queue<Job>& jobs, std::mutex& queueMutex, std::atomic<int>& jobCounter, std::chrono::steady_clock::time_point& lastPoint)
        : m_workerID(id),
        m_semaphore(sem),
        m_jobs(jobs),
        m_queueMutex(queueMutex),
        m_jobCounter(jobCounter),
        m_lastTimePoint(lastPoint),
        m_stopped(false)
    {
    }

    void start();
    void stop();

private:
    int m_workerID;
    Semaphore& m_semaphore;
    std::queue<Job>& m_jobs;
    std::mutex& m_queueMutex;
    std::atomic<int>& m_jobCounter;
    std::chrono::steady_clock::time_point& m_lastTimePoint;
    bool m_stopped;
    std::thread m_thread;

    void run();
    void processJobAsync(const Job& job);
};