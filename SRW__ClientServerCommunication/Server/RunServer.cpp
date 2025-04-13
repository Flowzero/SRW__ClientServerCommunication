
//
// RunServer.cpp
// ~~~~~~~~~~~~~
// 
// This is the main server file from where you run it.
// 
// Copyright (c) 2025 Flowzy 
// This project uses the Boost C++ Libraries (https://www.boost.org/).  
// Boost is distributed under the Boost Software License, Version 1.0.  
// A copy of the license is available at: https://www.boost.org/LICENSE_1_0.txt
//

#include <boost/asio.hpp>
#include <boost/program_options.hpp>

#if defined (_WIN32)
    #include "MSWindowsServer.h"

#elif defined (__linux__)
    #include "LinuxServer.h"
#endif

using namespace std;
using namespace boost::asio;

namespace opt = boost::program_options;

int main(int argc, char* argv[])
{
    #if defined (_WIN32)
        setlocale(LC_ALL, "Russian");
        std::system("chcp 1251");
    #endif

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

    #if defined (_WIN32)
        MSWindowsServer server(io_context, port_number);
    #elif defined (__linux__)
        LinuxServer server(io_context, port_number);
    #endif

    io_context.run();

    return 0;
}