#pragma once

//
// MSWindowsServer.h
// ~~~~~~~~~~~~~~~~~
// 
// This is a server class declaration for Windows OS.
// 
// Copyright (c) 2025 Flowzy 
// This project uses the Boost C++ Libraries (https://www.boost.org/).  
// Boost is distributed under the Boost Software License, Version 1.0.  
// A copy of the license is available at: https://www.boost.org/LICENSE_1_0.txt
//

#include <boost/asio.hpp>
#include <Windows.h>

#include "Server.h"
#include "ServerClient.h"


using boost::asio::io_context;


class MSWindowsServer : public Server
{
public:
	MSWindowsServer(io_context& io_context, unsigned short port);
	~MSWindowsServer();

protected:
	awaitable<void> start() override;
	
};
