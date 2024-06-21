#include "include/JobScheduler.h"

JobScheduler::JobScheduler(int numWorkers) : 
    m_semaphore(1),
    m_jobCounter(0) 
{
    for (int i = 0; i < numWorkers; ++i) {
        m_workers.emplace_back(i + 1, m_semaphore, m_jobs, m_queueMutex, m_jobCounter, m_lastTimePoint);
    }
}

JobScheduler::~JobScheduler() {
    stop();
}

void JobScheduler::start() {
    for (auto& worker : m_workers) {
        worker.start();
    }
}

void JobScheduler::stop() {
    for (auto& worker : m_workers) {
        worker.stop();
    }
}

void JobScheduler::addJob(const Job& job) {
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_jobs.push(job);
    }
}

int JobScheduler::getJobCounter() const {
    return m_jobCounter;
}

std::chrono::steady_clock::time_point JobScheduler::getLastTimePoint() {
    return m_lastTimePoint;
}