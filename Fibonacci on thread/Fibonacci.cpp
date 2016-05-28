#include <chrono>
#include <thread>
#include <cstdint>
#include <fstream>
#include <iostream>

#include "Fibonacci.hpp"

namespace spo {

Fibonacci::Fibonacci() : m_thread() {
    m_count = true;
    m_prevValue = 0;
    m_currentValue = 1;
}

Fibonacci::~Fibonacci() {
    if(m_thread.joinable()) {
        m_thread.join();
    }
}

void Fibonacci::Stop() {
    m_mutex.lock();
    m_count = false;
    m_mutex.unlock();
    if(m_thread.joinable()) {
        m_thread.join();
    }
}

void Fibonacci::Start() {
    m_count = true;
    m_thread = std::thread(&Fibonacci::Calculate, this);
}

void Fibonacci::Calculate() {
    m_mutex.lock();
    if (m_count) {
        u_int64_t tempValue;
        tempValue = m_prevValue + m_currentValue;
        m_prevValue = m_currentValue;
        m_currentValue = tempValue;
        m_mutex.unlock();
        PrintValue();
        std::chrono::milliseconds duration(250);
        std::this_thread::sleep_for(duration);
        Calculate();
    } else {
        m_mutex.unlock();
    }
}

void Fibonacci::PrintValue() {
    std::thread::id currentid = std::this_thread::get_id();
    std::cout << "id: " << currentid << " => Value: " << m_currentValue << std::endl;
}

} /* namespace spo */