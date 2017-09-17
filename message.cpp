#include <iostream>

#include "message.hpp"

Message::Message(string input_text) :
    m_input_text{input_text}
{
    cout << "Message created\n";
}

Message::~Message()
{
    cout << "Message destroyed\n";
}

Message::Message(Message& a) :
    m_input_text{a.m_input_text},
    m_promise_response{move(a.m_promise_response)}
{
    cout << "COPY contructed!\n";
}
Message::Message(Message&& a) :
    m_input_text{a.m_input_text},
    m_promise_response{move(a.m_promise_response)}
{
    cout << "Move contructed!\n";
}


future<string> Message::GetFutureReply()
{
    return m_promise_response.get_future();
}

void Message::SetResponse(std::string response)
{
    m_promise_response.set_value(response);
}
