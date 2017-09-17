#pragma once

#include <deque>
#include <future>
#include <thread>

#include "message.hpp"

using namespace std;
using spromise = promise<string>;

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
    std::thread m_thread;

    condition_variable m_queue_condition;
    mutex m_queue_mutex;
};
