#pragma once 

//
// Server.h
// ~~~~~~~~
// 
// This is a base class declaration for platform-dependent servers;
// 
// Copyright (c) 2025 Flowzy 
// This project uses the Boost C++ Libraries (https://www.boost.org/).  
// Boost is distributed under the Boost Software License, Version 1.0.  
// A copy of the license is available at: https://www.boost.org/LICENSE_1_0.txt
//

#include <boost/asio.hpp>
#include <set>

#include "ServerClient.h"


using boost::asio::ip::udp;
using boost::asio::awaitable;
using boost::asio::io_context;


class Server
{
protected:
    udp::socket sock;
    set<client_ptr> clients;                // base class client typedefed to client_ptr. The
                                            // set stores clients that can use different platforms
    udp::endpoint remote_endpoint;
    boost::array<char, 1> recv_conn_buff;   // used to register new incomming connections from clients
                                            // and determine their platform
    bool server_running = false;

    virtual awaitable<void> start() { co_return; };
    awaitable<void> receive_connections();  // the same method for all platforms

public:
    Server(io_context& io_context, unsigned short port);
    ~Server();

    bool is_running() const;
};

