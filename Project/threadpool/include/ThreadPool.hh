#include <thread>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <functional>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

class ThreadPool {
public:
        ThreadPool(uint32_t numthreads);
        ~ThreadPool();

        void Enqueue(function<void()> task);
        void Worker();
        void JoinAll();

        template <typename ClassFunction>
        void ParallelFor(uint32_t begin, uint32_t end) {

                int chunk = (end - begin) / m_nthreads;
                for (int i = 0; i < m_nthreads; ++i) {
                        Enqueue([=]{
                                        int threadstart = begin + i*chunk;
                                        int threadstop = (i == m_nthreads - 1) ? end : threadstart + chunk;
                                        for (int it = threadstart; it < threadstop; ++it) {
                                                ClassFunction::Serial(it);
                                        }
                                });
                }
        }

private:
        // threads and task queue
        int m_nthreads;
        vector<thread> m_workers;
        queue<function<void()>> m_tasks;

        // thread synchronization members
        bool stop_workers;
        condition_variable m_condition;
        mutable mutex m_taskmutex;

};
