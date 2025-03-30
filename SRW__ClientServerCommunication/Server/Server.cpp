
// 
// Server.cpp
// ~~~~~~~~~~
// 
// This is an asynchronous server capable of handling multiple connections.
// The current assumption is that the server and clients are running on the same machine.
// 
// Known issues: no client disconnect handler.
// 
// 
// Copyright (c) 2025 Flowzy 
// This project uses the Boost C++ Libraries (https://www.boost.org/).  
// Boost is distributed under the Boost Software License, Version 1.0.  
// A copy of the license is available at: https://www.boost.org/LICENSE_1_0.txt
// 

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/system.hpp>

#include <boost/program_options.hpp>

#include <iostream>
#include <string>
#include <set>

#include "ServerClient.h"

#if defined (_WIN32)
	#include <Windows.h>
#endif


using namespace std;
using namespace boost;

using boost::asio::ip::udp;
using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::awaitable;
using boost::asio::use_awaitable;

namespace opt = boost::program_options;


// create other server classes for specific platforms


class UDPServer
{
    private:
        udp::socket sock;
        set<client_ptr> clients;
        udp::endpoint remote_endpoint;

        boost::array<char, 1> recv_buffer;
        bool server_running;


        awaitable<void> start() {
            while (server_running)
            {
                try
                {
                    asio::steady_timer timer(co_await asio::this_coro::executor);

                    cout << "Server is running" << endl;

                #if defined (_WIN32)
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
                                    asio::buffer(message), client->get_endpoint(),
                                    use_awaitable
                                );
                            }
                            cout << "Sent cursor data: " << message << endl;
                        }
                    }
                    timer.expires_after(chrono::milliseconds(100));
                    co_await timer.async_wait(use_awaitable);
                #endif
                }

                catch (boost::system::error_code& ec)
                {
                    cerr << "Error in the start()";
                }
            }
        }

        awaitable<void> recieve_connections() {
            while (server_running)
            {
                try
                {
                    asio::steady_timer timer(co_await asio::this_coro::executor);

                    size_t bytes_recievd = co_await sock.async_receive_from(
                        asio::buffer(recv_buffer), remote_endpoint, use_awaitable
                    );

                    bool client_exists = false;
                    for (const auto& client : clients) {
                        if (client->get_endpoint() == remote_endpoint) {
                            client_exists = true;
                            break;
                        }
                    }

                    if (!client_exists)
                    {
                        auto new_client = make_shared<WINDOWS_client>(remote_endpoint);
                        // add condition to create obj of a platform-orientated class

                        clients.insert(new_client);
                        cout << "New client connected: "
                            << remote_endpoint.address().to_string()
                            << remote_endpoint.port() << endl;

                    }
                    timer.expires_after(chrono::milliseconds(100));
                    co_await timer.async_wait(use_awaitable);
                }
                catch (system::system_error& err)
                {
                    if (err.code() != boost::asio::error::operation_aborted)
                        cerr << "Receive error: " << err.what() << endl;
                }
            }
        }

    public:
        UDPServer(asio::io_context& io_context, unsigned short port)
            : sock(io_context, udp::endpoint(udp::v4(), port)), server_running(true) {
            co_spawn(io_context, start(), detached);
            co_spawn(io_context, recieve_connections(), detached);
        }
        ~UDPServer() {
            server_running = false;
            sock.close();
        }

        bool is_running() const { return server_running; }
};


int main(int argc, char* argv[])
{
    opt::options_description desc("All options");
    desc.add_options()
        ("port_number", opt::value<unsigned short>()->default_value(3333), "Specify port number you want to run server on")
        ("IPv4_6", opt::value<string>(), "Specify IP version (IPv4 or IPv6)")
        ("help", "produce help message")
        ;
    opt::variables_map vm;
    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    opt::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return 1;
    }


    unsigned short port_number = vm["port_number"].as<unsigned short>();
    asio::io_context io_context;

    UDPServer server(io_context, port_number);
    io_context.run();

    return 0;
}
