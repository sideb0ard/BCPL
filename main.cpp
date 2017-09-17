#include <iostream>
#include <thread>
#include "bot.hpp"

using namespace std;

int main()
{
    Bot bot;

    string input_line;

    cout << "> ";
    while(getline(cin, input_line))
    {
        if (input_line.size() != 0)
        {
            future<string> fut = bot.converse(input_line);
            string reply = fut.get();
            cout << reply << endl;
        }

        cout << "> ";
    }
    cout << "byeeee" << endl;
}
