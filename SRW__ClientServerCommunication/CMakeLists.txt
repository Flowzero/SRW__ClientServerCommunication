﻿
add_executable (SRW__ClientServerCommunication   "Server/Server.cpp" "Client/Client.cpp" "Server/ServerClient.h" "Server/RunServer.cpp" "Server/Server.h" "Server/MSWindowsServer.h" "Server/MSWindowsServer.cpp" "Server/LinuxServer.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SRW__ClientServerCommunication PROPERTY CXX_STANDARD 20)
endif()

