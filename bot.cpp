#include <iostream>

#include "bot.hpp"
#include "message.hpp"

using namespace std;

Bot::Bot() :
    m_converse_queue{},
    m_thread{&Bot::Run, this}
{
    cout << "Bot starting up\n";
}

Bot::~Bot()
{
    cout << "Bot say gbye\n";
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
    while(true)
    {
        unique_lock<mutex> lck{m_queue_mutex};
        m_queue_condition.wait(lck);
        cout << "Got a condition!\n";
        auto msg = move(m_converse_queue.front());
        m_converse_queue.pop_front();
        msg->SetResponse("jobbie");
        cout << "Got a reply\n";
        lck.unlock();
    }
}


