#include "ThreadPool.h"

namespace NGroupingChallenge {
    ThreadPool::ThreadPool(size_t num_threads)
        : stop(false)
    {
        for (size_t i = 0; i < num_threads; ++i) {
            threads.emplace_back([this] {
                while (true) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(
                            queueMutex);

                        cv.wait(lock, [this] {
                            return !tasks.empty() || stop;
                        });

                        if (stop && tasks.empty()) {
                            return;
                        }

                        task = std::move(tasks.front());
                        tasks.pop();
                    }

                    task();
                }
            });
        }
    }

    ThreadPool::~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }

        cv.notify_all();

        for (auto& thread : threads) {
            thread.join();
        }
    }

    void ThreadPool::enqueue(std::function<void()> task) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.emplace(move(task));
        }
        cv.notify_one();
    }
} // NGroupingChallenge