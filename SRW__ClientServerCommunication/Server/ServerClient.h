#pragma once

// 
// ServerClient.h
// ~~~~~~~~~~
// 
// This header file contains definitions of three classes: client, WINDOWS_client, and LINUX_client. 
// These classes are used for the respective platform.
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

#include <iostream>
#include <string>

// for the future methods realization 
#if defined (_WIN32)
    #include <Windows.h>
#endif

using namespace std;
using namespace boost;

using boost::asio::ip::udp;


class client
{
    protected:
        udp::endpoint ep;

    public:
        client(udp::endpoint& endpoint) : ep(endpoint) {}
        udp::endpoint get_endpoint() const { return ep; };
        
        // platoform specific methods = virtual methods
};
typedef std::shared_ptr<client> client_ptr;


class WINDOWS_client : public client,
                       public std::enable_shared_from_this<WINDOWS_client>
{
    public:
        WINDOWS_client(udp::endpoint& ep) : client(ep) {}
        // override platform specific methods
};


class LINUX_client : public client,
                     public std::enable_shared_from_this<LINUX_client>
{
    public:
        LINUX_client(udp::endpoint& ep) : client(ep) {}
};      // override platform specific methods
