#pragma once

#include <deque>
#include <future>
#include <thread>

#include "message.hpp"

using namespace std;

class Bot
{
public:
    Bot();
    ~Bot();
    std::future<std::string> converse(std::string);

private:
    void Run();

private:
    std::deque<unique_ptr<Message>> m_converse_queue;
    bool m_active;

    condition_variable m_queue_condition;
    mutex m_queue_mutex;

    std::thread m_thread;
};
