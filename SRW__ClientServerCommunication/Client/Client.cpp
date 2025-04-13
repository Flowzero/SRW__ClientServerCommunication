/*
//
// Client.cpp
// ~~~~~~~~~~
// 
// This is a very simple client that establishes a connection to the server.
// Both the server and the client are running on the same machine, so there is no
// need to resolve the address. 
//
// 
// Copyright (c) 2025 Flowzy 
// This project uses the Boost C++ Libraries (https://www.boost.org/).  
// Boost is distributed under the Boost Software License, Version 1.0.  
// A copy of the license is available at: https://www.boost.org/LICENSE_1_0.txt
// 

#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <iostream>
#include <string>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

using boost::asio::ip::udp;


// create other client classes for specific platforms


int main()
{
    #if defined (_WIN32)
        setlocale(LC_ALL, "Russian");
        std::system("chcp 1251");
    #endif

    try
    {
        io_context io;
        udp::socket socket(io, udp::v4());
        udp::endpoint server_endpoint(
            ip::make_address("127.0.0.1"), 3333
        );
        
        socket.send_to(buffer(""), server_endpoint);

        while (true)
        {
            boost::array<char, 128> recv_buf;
            udp::endpoint sender;
            size_t len = socket.receive_from(buffer(recv_buf), sender);
            cout << "Received: " << string(recv_buf.data(), len) << std::endl;
        }
    }
    catch (exception& e)
    {
        cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
*/