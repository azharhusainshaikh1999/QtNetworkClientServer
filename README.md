# Qt Client-Server Network Programming

## Overview
This project demonstrates a simple **Client-Server** application implemented using **C++** and **Qt 5.12.12**. It showcases basic TCP/IP network programming concepts with Qt's networking classes.

---

## Features
- TCP-based communication between client and server
- Server listens for incoming client connections
- Client connects to server using IP address and port
- Simple message exchange between client and server

---

## Prerequisites
- Qt 5.12.12 installed
- C++ compiler compatible with Qt 5.12.12
- Basic understanding of Qt and TCP/IP networking

---

## Build and Run Instructions

### Step 1: Build and Run the Server
1. Open the server project in Qt Creator.
2. Build the project.
3. Run the server application.
4. The server will start listening on a specified port.

### Step 2: Build and Run the Client
1. Open the client project in Qt Creator.
2. Build the project.
3. Run the client application.
4. Enter the server's **IP address** and **port number**.
5. Click **Start Server Connect** to establish a connection.
6. Send messages to the server once connected.

---

## Usage
- Start the server first to listen for incoming connections.
- Then start the client, input the server IP and port, and connect.
- Use the client interface to send messages to the server.
- Server will display received messages.

---

## Code Structure
- `server/` — Contains the server application source code.
- `client/` — Contains the client application source code.
- Both use Qt's `QTcpServer` and `QTcpSocket` classes for networking.

---

## Contact
For questions or suggestions, feel free to open an issue or contact me directly.

---

Happy coding! 🚀
