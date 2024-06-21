#include "include/Semaphore.h"

void Semaphore::notify() {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_count++;
    m_condition.notify_one();
}

void Semaphore::wait() {
    std::unique_lock<std::mutex> lock(m_mutex);
    while (m_count == 0) {
        m_condition.wait(lock);
    }
    m_count--;
}