# Merc

**Merc** is a lightweight HTTP server framework being built from scratch in modern C++ to understand the internals of web servers, HTTP request processing, routing, socket programming, and multithreaded networking.

> 🚧 **Project Status:** Under Active Development

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

- Winsock initialization using `WSAStartup()`
- TCP socket creation using `socket()`
- Binding the server socket to a specified port using `bind()`
- Listening for incoming client connections using `listen()`
- Accepting client connections using `accept()`
- Receiving client requests using `recv()`
- Sending responses using `send()`
- Basic socket and binding error handling
- Basic HTTP `200 OK` response

## Current Server Flow

```text
WSAStartup()
    ↓
socket()
    ↓
bind()
    ↓
listen()
    ↓
accept()
    ↓
recv()
    ↓
send()