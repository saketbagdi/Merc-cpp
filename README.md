# Merc

**Merc** is a lightweight HTTP server framework being built from scratch in modern C++ to understand the internals of web servers, HTTP request processing, routing, socket programming, and multithreaded networking.

> **Project Status:** Under Active Development

## Features Implemented

- Basic framework architecture
- Request and Response abstractions
- Error handling interface
- Callback-based routing
- URL routing infrastructure using `std::map`
- Response buffering using `std::forward_list`
- Content-Type support
- Validator interface for URL, MIME type, and path validation
- Static resource folder configuration
- Sample HTML endpoints

### Socket Programming

- Cross-platform socket-related implementation using conditional compilation
- TCP socket creation
- Binding the server socket to a specified port
- Listening for incoming client connections
- Accepting client connections
- Receiving client requests using `recv()`
- Sending HTTP responses using `send()`
- Basic socket error handling
- Basic HTTP `200 OK` response
- Client socket closure after request processing
- Platform-specific socket API cleanup

### Request Receiving and Buffering

- Request data can be received in multiple chunks
- Fixed-size request buffer with additional space reserved for null termination
- `recv()` is instructed to receive one byte less than the total buffer size
- Each received chunk is null-terminated before being stored
- Received chunks are stored using `std::forward_list`
- Number of received chunks is tracked
- Total request data size is calculated
- A dynamically allocated buffer is created for the complete request
- All received chunks are combined into a single request buffer
- Complete request data is null-terminated and ready for parsing
- Dynamically allocated request data is released after processing

## Current Server Flow

```text
Initialize Platform Socket API
        ↓
socket()
        ↓
bind()
        ↓
listen()
        ↓
accept()
        ↓
Receive Request Data
        ↓
Assemble Complete Request
        ↓
Request Parsing
        ↓
Generate Response
        ↓
send()
        ↓
Close Client Socket
        ↓
Cleanup Platform Socket API

## Current Request Receiving Flow

accept()
    ↓
recv() request chunk
    ↓
Add '\0' to the received chunk
    ↓
Store chunk in std::forward_list
    ↓
Receive next chunk
    ↓
Repeat until recv() returns 0
    ↓
Calculate total request size
    ↓
Allocate memory for complete request data
    ↓
Copy all chunks into the complete request buffer
    ↓
Add final '\0'
    ↓
Request ready for parsing
    ↓
Release request memory
    ↓
Close client socket






