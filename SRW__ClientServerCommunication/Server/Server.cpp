
//
// Server.cpp
// ~~~~~~~~~~
// 
// These are methods for base class (Server)
// 
// Copyright (c) 2025 Flowzy 
// This project uses the Boost C++ Libraries (https://www.boost.org/).  
// Boost is distributed under the Boost Software License, Version 1.0.  
// A copy of the license is available at: https://www.boost.org/LICENSE_1_0.txt
//

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/system.hpp>

#include "Server.h"
#include "ServerClient.h"


using namespace std;
using namespace boost::asio;

using boost::asio::co_spawn;
using boost::asio::awaitable;
using boost::asio::use_awaitable;

Server::Server(asio::io_context& io_con, unsigned short port)
	: sock(io_con, udp::endpoint(udp::v4(), port)), server_running(true)
{
	// do noting 
}

Server::~Server()
{
	server_running = false;
	sock.close();
}

bool
Server::is_running() const
{
	return server_running;
}

awaitable<void>
Server::receive_connections()
{
	while (server_running)
	{
		try
		{
			asio::steady_timer timer(co_await asio::this_coro::executor);
			size_t bytes_recievd = co_await sock.async_receive_from(
				asio::buffer(recv_conn_buff),
				remote_endpoint,
				use_awaitable
			);

			bool client_exists = false;
			for (const auto& client : clients)
			{
				if (client->get_endpoint() == remote_endpoint)
				{
					client_exists = true;
					break;
				}
			}

			if (!client_exists)
			{
				/*
				// determinate client's platform
				string client_platform = [this] {
					return "WINDOWS";
					}();

				client_ptr new_client;
				if (client_platform == "WINDOWS") {
					auto new_client = make_shared<WINDOWS_client>(remote_endpoint);
				}
				else if (client_platform == "LINUX") {
					auto new_client = make_shared<LINUX_client>(remote_endpoint);
				}
				*/
				auto new_client = make_shared< WINDOWS_client>(remote_endpoint);
				 
				clients.insert(new_client);
				cout << "New client connected: "
					<< remote_endpoint.address().to_string()
					<< remote_endpoint.port() << endl;
			}
			timer.expires_after(std::chrono::milliseconds(100));
			co_await timer.async_wait(use_awaitable);
		}
		catch (boost::system::system_error& err)
		{
			if (err.code() != boost::asio::error::operation_aborted)
			{
				cerr << "Receive error: " << err.what() << endl;
			}
		}
	}
}