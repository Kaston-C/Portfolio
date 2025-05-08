# Simple HTTP Server

This is a simple multi-threaded HTTP server written in C++. It listens on port 8080 and serves static files from a local directory (`web_files`). It handles basic HTTP requests and can return content types for HTML, CSS, JavaScript, and image files. Also includes a picture of my cat, served as part of the web content!

## Features

* Handles HTTP GET requests.
* Serves HTML, CSS, JavaScript, and image files.
* Returns a `404 Not Found` page if the requested file is not found.
* Prevents access to certain error pages (e.g., `/404.html`, `/403.html`).
* Supports Keep-Alive connections for persistent connections.
* Uses multiple threads to handle each client concurrently.

## Dependencies

* C++11 or later.
* Standard C++ libraries for networking (`<sys/socket.h>`, `<arpa/inet.h>`, etc.).

## Compilation and Running

### Compile the Server

```bash
g++ main.cpp -o server
```

### Run the Server

```bash
./server
```

The server will start listening on port `8080`. You can access it in your web browser by navigating to `http://localhost:8080`.

## File Structure

* `main.cpp`: The C++ source code for the server.
* `web_files/`: A directory where you store the static files (HTML, CSS, JS, images) that the server will serve.
* `web_files/404.html`: A custom 404 error page served when a file is not found.
* `web_files/403.html`: Forbidden access page for restricted resources.

## Request Handling

The server handles incoming HTTP GET requests, extracts the file path, and serves the file from the `web_files` directory. If the requested file is not found, it serves a `404 Not Found` page. If an attempt is made to access certain error pages like `/404.html` or `/403.html`, the server will respond with a `403 Forbidden` status.

### Example Request

When accessing `http://localhost:8080/index.html`, the server will look for the file `web_files/index.html` and return it.

### Default File

If the root URL `/` is requested, the server will return the file `web_files/index.html` by default.

## Error Handling

* If the file cannot be opened (e.g., it doesn't exist), the server will return a `404 Not Found` page.
* Access to error pages like `404.html` and `403.html` is forbidden, returning a `403 Forbidden` status.