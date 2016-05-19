#pragma once

#include <mutex>
#include <string>
#include <thread>
#include <condition_variable>

namespace spo {

static std::mutex mutex;
static bool isEnable = true;
static std::condition_variable conditionVariale;


class Fibonacci {
public:
    Fibonacci();
    ~Fibonacci();

    void Stop();
    void Start();
    void Calculate();
    void PrintValue();
private:
    bool m_count;
    std::mutex m_mutex;
    std::thread m_thread;
    u_int64_t m_prevValue;
    u_int64_t m_currentValue;
};

} /* namespace spo */