#include "ThreadPool.h"

#include <iostream>

ThreadPool::ThreadPool(size_t threads)
{
    for (size_t i = 0; i < threads; i++)
    {
        _threads.emplace_back([this]
                              {
            while (true)
            {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(_queueMutex);

                    _cv.wait(lock, [this]
                             { return !_tasks.empty() || _stop; });

                    task = std::move(_tasks.front());
                    _tasks.pop();
                }
                try
                {
                    task();
                }
                catch (std::exception &e)
                {
                    std::cout << e.what();
                }
            
                                } });
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::scoped_lock<std::mutex> lock(_queueMutex);
        _stop = true;
    }

    _cv.notify_all();

    for (auto &thread : _threads)
    {
        thread.join();
    }
}
