#include <chrono>
#include "include/JobScheduler.h"

int main() {
    JobScheduler scheduler(10); // Create a scheduler with 10 worker threads

    // Adding jobs to the scheduler
    for (int i = 1; i <= 20; ++i) {
        Job job{ i, "Job " + std::to_string(i), rand() % 500 + 250 }; // Random duration between 250 ms and 750 ms
        scheduler.addJob(job);
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Start the scheduler and workers
    scheduler.start();

    // Wait for a while to simulate job scheduling
    std::this_thread::sleep_for(std::chrono::seconds(12));

    // Stop the scheduler and workers
    scheduler.stop();

    auto end = scheduler.getLastTimePoint();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Display total number of jobs processed
    std::cout << "Total jobs processed: " << scheduler.getJobCounter() << std::endl;
    std::cout << "Elapsed time: " << duration.count() << " milliseconds\n";

    return 0;
}