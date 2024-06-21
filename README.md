# Concurrency Example

In this example, a job scheduler is implemented. Number of worker threads in this scheduler is set in scheduler's constructor.
Let's imagine we pass 2 as number of worker threads. In this case, scheduler creates two worker threads and passes the it's following class members to each worker thread instance:

- Semaphore (which is defined as 1). This semaphore is used to protect std::cout operation to print separately and safe. Each worker thread use the same semaphore object.
- Job queue. All added jobs to scheduler are also passed to all worker thread instances. Every time there is still a a job in the queue, worker thread will get a job to process.
- Queue mutex. This is also passed to all worker thread instances to protect operations (front, pop) on the job queue.
- Job counter. This is also passed to count the total number of jobs processed to print such information at the end.
- Last time point is also passed to measure the elapsed time to print such information at the end.

Then we tell scheduler to add 10 different jobs with different job ID, job name and waiting times. Scheduler populates it's job queue with those jobs.

Then we tell scheduler to start. This triggers all created worker threads to start running, this is where std::thread class member is ran with again a class method run().
Run method keeps running in a while loop until it's stopped. As long as it's running, it's checking if job queue is empty. If not, it's getting a job and starts processing it asynchronously.
Async method waits a specified amount of time and then uses the semaphore to avoid conflicts in logging.

After waiting 6 seconds for all possible jobs to be completed, we get the elapsed time and print on console.
With different number of worker threads, we must see different results.

#### 1 worker thread: it takes 5589 milliseconds on 10 different jobs - 11804 milliseconds on 20 different jobs

#### 2 worker threads: it takes 2859 milliseconds on 10 different jobs - 6027 milliseconds on 20 different jobs

#### 5 worker threads: it takes 1457 milliseconds on 10 different jobs - 2736 milliseconds on 20 different jobs

#### 10 worker threads: it takes 1249 milliseconds on 10 different jobs - 1788 milliseconds on 20 different jobs
