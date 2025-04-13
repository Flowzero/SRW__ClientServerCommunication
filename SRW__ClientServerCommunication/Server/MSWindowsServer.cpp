
//
// MSWindowsMSWindowsServer.cpp
// ~~~~~~~~~~~~~~~~~~~
// 
// These are methods for MSWindowsMSWindowsServer class
// 
// Copyright (c) 2025 Flowzy 
// This project uses the Boost C++ Libraries (https://www.boost.org/).  
// Boost is distributed under the Boost Software License, Version 1.0.  
// A copy of the license is available at: https://www.boost.org/LICENSE_1_0.txt
//

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/system.hpp>

#include "MSWindowsServer.h"
#include "ServerClient.h"


using namespace std;
using namespace boost::asio;

using boost::asio::co_spawn;
using boost::asio::awaitable;
using boost::asio::use_awaitable;

MSWindowsServer::MSWindowsServer(asio::io_context& io_cont, unsigned short port)
    : Server(io_cont, port)
{
    co_spawn(io_cont, start(), detached);
    co_spawn(io_cont, receive_connections(), detached);
}

MSWindowsServer::~MSWindowsServer()
{
    server_running = false;
    sock.close();
}

awaitable<void>
MSWindowsServer::start()
{
    while (server_running)
    {
        try
        {
            asio::steady_timer timer(co_await asio::this_coro::executor);
            cout << "Server is running" << endl;

            if (clients.size())
            {
                POINT cursorPos;
                if (GetCursorPos(&cursorPos))
                {
                    string message = to_string(cursorPos.x) + " " +
                        to_string(cursorPos.y);

                    for (auto client : clients)
                    {
                        co_await sock.async_send_to(
                            asio::buffer(message),
                            client->get_endpoint(),
                            use_awaitable
                        );
                    }
                    cout << "Sent cursor data: " << message << endl;
                }
            }
            timer.expires_after(std::chrono::milliseconds(100));
            co_await timer.async_wait(use_awaitable);
        }

        catch (boost::system::error_code& ec)
        {
            cerr << "Error in the start()";
        }
    }
}