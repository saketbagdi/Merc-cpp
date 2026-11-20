# Merc

A lightweight HTTP server framework written from scratch in C++ on raw TCP sockets, built to understand how web servers work internally: socket programming, request handling, routing and (next) concurrency.

> **Status: early development.** The TCP server loop, request buffering and route registration work. Request parsing, sending HTTP responses and handler dispatch are the next milestones. See [Current status](#current-status) and the [Roadmap](#roadmap).

## Current status

| Area | Status |
|---|---|
| TCP server: `socket()`, `bind()`, `listen()`, `accept()` | Implemented |
| Receiving a request in chunks and assembling it into one buffer (`recv()`, `std::forward_list`) | Implemented |
| Route registration with callbacks (`std::map` of URL to function pointer) | Implemented (`get()` only) |
| `Response` object that buffers content and tracks content length | Implemented |
| `Error` type and error callback for startup failures | Implemented |
| Windows socket setup (Winsock) | Implemented |
| `Validator` (URL, MIME type, path) | Interface only; checks currently accept everything |
| Static resources folder | Setter only; files are not served yet |
| `Request` class | Placeholder (empty) |
| HTTP request parsing | Not yet |
| Dispatching requests to registered handlers | Not yet |
| Sending HTTP responses (status line, headers, body) | Not yet |
| Linux build | Not yet (known issues listed in the roadmap) |
| Multithreading / concurrent clients | Not yet (one connection at a time) |
| Tests | Not yet |

## How it works today

```text
listen(port)
    |
    v
socket() -> bind() -> listen() -> accept()   (loops forever)
    |
    v
recv() chunks into std::forward_list<string>
    |
    v
assemble chunks into one dynamically allocated buffer
    |
    v
print raw request to the console
    |
    v
[next] parse request -> match route -> call handler -> send response
    |
    v
close client socket
```

At the moment the server receives and prints each raw request. It does not yet send a response back to the client.

## Usage

This is how the framework is meant to be used (see `main()` in `merc.cpp`):

```cpp
Merc merc;
merc.setStaticResourcesFolder("static");

merc.get("/", [](Request &request, Response &response) -> void {
    response.setContentType("text/html");
    response << "<h1>Welcome</h1>";
});

merc.listen(6060, [](Error &error) -> void {
    if (error.hasError()) { cout << error.getError(); return; }
    cout << "Merc HTTP Server is ready to accept request at port 6060" << endl;
});
```

Route registration and startup work today. Handlers are registered but not yet called, because request parsing and dispatch are not implemented.

## Build and run

**Windows (g++ / MinGW-w64):**

```bat
g++ -std=c++11 merc.cpp -o merc.exe -lws2_32
merc.exe
```

The server listens on port `6060`. Open `http://localhost:6060/` in a browser and watch the console to see the raw request the server receives.

**Linux:** does not build yet. See the roadmap.

## Roadmap

In priority order:

- [ ] Send a valid HTTP response (status line, `Content-Type`, `Content-Length`, body)
- [ ] Parse the request line and headers and populate `Request`
- [ ] Dispatch requests to registered handlers; return 404 for unknown routes
- [ ] Read until the end of the headers (`\r\n\r\n`) instead of waiting for the client to close the connection, and handle `recv()` errors
- [ ] Fix the Linux build (`<arpa/inet.h>` include, `closesocket`/`close` per platform, `__linux__` macro, link flags)
- [ ] Serve static files from the static resources folder with correct MIME types
- [ ] Implement the `Validator` checks
- [ ] Handle multiple clients (thread per connection, then a thread pool)
- [ ] Support `POST`, query strings and more status codes
- [ ] Split `merc.cpp` into headers and sources; add a `Makefile` or `CMakeLists.txt`
- [ ] Add tests

## Author

**Saket Bagdi**: [GitHub](https://github.com/saketbagdi) · saket.bagdi@gmail.com
