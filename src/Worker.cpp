#include <iostream>
#include <future>

#include "include/Worker.h"

void Worker::start() {
    m_thread = std::thread(&Worker::run, this);
}

void Worker::stop() {
    if (m_stopped == false) {
        m_stopped = true;
        m_thread.join();
    }
}

void Worker::run() {
    while (!m_stopped) {
        Job job;
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            if (!m_jobs.empty()) {
                job = std::move(m_jobs.front());
                m_jobs.pop();
            }
        }

        if (!job.jobName.empty()) {
            processJobAsync(job);
        }
    }
}

void Worker::processJobAsync(const Job& job) {
    // Asynchronously process the job
    auto future = std::async(std::launch::async, [this, job] {
        // Simulate job execution time
        std::this_thread::sleep_for(std::chrono::milliseconds(job.jobDurationMs));
        m_semaphore.wait();
        std::cout << "Worker " << m_workerID << " finished job " << job.jobName << " (ID: " << job.jobID << ")" << std::endl;
        m_semaphore.notify();
        m_jobCounter++;
        m_lastTimePoint = std::chrono::high_resolution_clock::now();
    });
}