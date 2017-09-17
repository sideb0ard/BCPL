#include <iostream>
#include <chrono>

#include "bot.hpp"
#include "message.hpp"

using namespace std;

Bot::Bot() :
    m_converse_queue{},
    m_active{true},
    m_thread{&Bot::Run, this}
{
    cout << "Bot starting up\n";
}

Bot::~Bot()
{
    cout << "Bot say gbye\n";
    m_active = false;
    m_thread.join();
}

std::future<std::string> Bot::converse(std::string input)
{
    cout << "COnverse received " << input << endl;
    unique_ptr<Message> m{new Message{input}};

    future<string> freply = m->GetFutureReply();

    unique_lock<mutex> lck{m_queue_mutex};
    m_converse_queue.push_back(move(m));
    m_queue_condition.notify_one();

    return freply;
}

void Bot::Run()
{
    while(m_active)
    {
        unique_lock<mutex> lck{m_queue_mutex};
        //m_queue_condition.wait_for(lck, std::chrono::microseconds(10));
        while  (m_queue_condition.wait_for(lck, std::chrono::milliseconds(100)) != std::cv_status::timeout)
        {
            cout << "Got a condition!\n";
            auto msg = move(m_converse_queue.front());
            m_converse_queue.pop_front();
            msg->SetResponse("jobbie");
            cout << "Got a reply\n";
        }
        lck.unlock();
    }
}


