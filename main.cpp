#include <iostream>
#include <thread>
#include "bot.hpp"

using namespace std;

int main()
{
    Bot bot;

    string input_line;

    while(true)
    {
        getline(cin, input_line);
        future<string> fut = bot.converse(input_line);
        string reply = fut.get();
        cout << reply << endl;
    }
}
