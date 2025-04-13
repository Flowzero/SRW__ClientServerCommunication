#pragma once

//
// LinuxServer.h
// ~~~~~~~~~~~~~~~~~
// 
// This is a server class declaration for Linux OS.
// 
// Copyright (c) 2025 Flowzy 
// This project uses the Boost C++ Libraries (https://www.boost.org/).  
// Boost is distributed under the Boost Software License, Version 1.0.  
// A copy of the license is available at: https://www.boost.org/LICENSE_1_0.txt
//

#include <boost/asio.hpp>
// include linux dependencies 


#include "Server.h"
#include "ServerClient.h"


using boost::asio::io_context;


class LinuxServer : public Server
{
public:
	LinuxServer(io_context& io_context, unsigned short port);

protected:
	awaitable<void> start() override;
};
