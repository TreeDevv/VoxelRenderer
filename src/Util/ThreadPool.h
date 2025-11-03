#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>

class ThreadPool
{
public:
    ThreadPool(size_t threads = std::thread::hardware_concurrency());

    template <typename F, typename... A>
    void submit(F &&task, A &&...args)
    {
        {
            std::scoped_lock<std::mutex> lk(_queueMutex);
            _tasks.emplace([func = std::forward<F>(task), ... args = std::forward<A>(args)]() mutable
                           { std::invoke(std::move(func), std::move(args)...); });
        }
    }

    ~ThreadPool();

private:
    bool _stop = false;

    std::queue<std::function<void()>> _tasks;
    std::vector<std::thread> _threads;

    std::mutex _queueMutex;
    std::condition_variable _cv;
};
