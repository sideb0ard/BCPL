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
    m_future_string_holder{move(a.m_future_string_holder)}
{
    cout << "COPY contructed!\n";
}
Message::Message(Message&& a) :
    m_input_text{a.m_input_text},
    m_future_string_holder{move(a.m_future_string_holder)}
{
    cout << "Move contructed!\n";
}


future<string> Message::GetFutureReply()
{
    return m_future_string_holder.get_future();
}

void Message::SetResponse(std::string response)
{
    m_future_string_holder.set_value(response);
}
