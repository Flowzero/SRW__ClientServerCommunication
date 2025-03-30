## Introduction ##
This is a project for my Scientific Research Work (SRW) for Volgograd State University for the 4th semester in the direction of "Software Engineering".

This repository includes a minimum viable product (MVP), namely a UDP server that tracks the cursor position and sends its coordinates to all connected devices in real time. Based on this repository, a larger project will be built: a software keyboard, video, mouse (KVM) cross-platform switch. The project is inspired by [Mouse Without Borders](https://www.microsoft.com/en-us/download/details.aspx?id=35460) and [Input Leap](https://github.com/input-leap/input-leap).

## Features ##
This is a basic functionality build from 30.03.2025

**Server:**
- Accepts local UDP connections (at 127.0.0.1). There is no resolver yet
- Sends cursor cooradinates every 100 ms
- Platform-dependent (for now only Windows)

Known Issues: no handler for client terminating connection case (Receive error: Connection not established because the destination computer rejected the connection request)

**Client:**
- Establishing connection to the server at the specified IP and port
- Receiving and outputting the received cursor coordinates to the console

## How to use ##
Compile Server.cpp and Client.cpp to get exe files. Run Server.exe and only after that Client.exe (The order is important). Now the server is handling one client. You can run the Client.exe again to emulate multiple connections.

## Licenses ##
The software product uses the [Boost C++ Libraries](https://www.boost.org/).  
Boost is distributed under the Boost Software License, Version 1.0.  
A copy of the license is available [here](https://www.boost.org/LICENSE_1_0.txt).

This project is licensed under the MIT License.



