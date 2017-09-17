#pragma once

#include <future>
#include <string>

using namespace std;

class Message
{
public:
    Message(string input_text);
    ~Message();

    Message(Message& a);
    Message& operator=(Message& a);

    Message(Message&& a);
    Message& operator=(Message&& a);

    future<string> GetFutureReply();
    void SetResponse(std::string response);

private:
    string m_input_text;
    std::promise<string> m_future_string_holder;
};
