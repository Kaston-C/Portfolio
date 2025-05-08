#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>

#define PORT 8080

bool ends_with(const std::string &str, const std::string &suffix) {
    if (str.length() < suffix.length()) return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

void serve_file(int client_socket, const char* filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        // Send 404 if file couldn't be opened
        std::ifstream error_file("web_files/404.html", std::ios::in | std::ios::binary);
        if (error_file.is_open()) {
            std::string error_contents((std::istreambuf_iterator<char>(error_file)), std::istreambuf_iterator<char>());
            std::string error_header =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: " + std::to_string(error_contents.size()) + "\r\n\r\n";
            write(client_socket, error_header.c_str(), error_header.size());
            write(client_socket, error_contents.c_str(), error_contents.size());
        } else {
            const char *fallback =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 13\r\n\r\n"
                "File Not Found";
            write(client_socket, fallback, strlen(fallback));
        }
        return;
    }

    std::string file_contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Determine Content-Type based on file extension
    std::string fname = filename;
    std::string content_type = "text/plain";

    if (ends_with(fname, ".html") || ends_with(fname, ".htm")) content_type = "text/html";
    else if (ends_with(fname, ".css")) content_type = "text/css";
    else if (ends_with(fname, ".js")) content_type = "application/javascript";
    else if (ends_with(fname, ".png")) content_type = "image/png";
    else if (ends_with(fname, ".jpg") || ends_with(fname, ".jpeg")) content_type = "image/jpeg";
    else if (ends_with(fname, ".gif")) content_type = "image/gif";

    std::string header =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: " + content_type + "\r\n" +
        "Content-Length: " + std::to_string(file_contents.size()) + "\r\n" +
        "Connection: keep-alive\r\n" + // Add Keep-Alive header
        "\r\n";

    write(client_socket, header.c_str(), header.size());
    write(client_socket, file_contents.c_str(), file_contents.size());
}

void handle_client(int new_socket) {
    char buffer[50000] = {0};
    read(new_socket, buffer, 50000);

    // Extract the file requested from the GET request
    std::string request(buffer);
    std::string file_requested = "/index.html";  // Default file

    size_t pos = request.find("GET ");
    if (pos != std::string::npos) {
        size_t end_pos = request.find(" HTTP/1.1");
        if (end_pos != std::string::npos) {
            file_requested = request.substr(pos + 4, end_pos - pos - 4);  // Extract filename
        }
    }

    // If root path is requested, default to index.html
    if (file_requested == "/") {
        file_requested = "/index.html";
    }

    // === Check to prevent access to error pages ===
    if (file_requested == "/404.html" || file_requested == "/403.html") {
        const char *forbidden_response =
            "HTTP/1.1 403 Forbidden\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n\r\n"
            "Forbidden";
        write(new_socket, forbidden_response, strlen(forbidden_response));
        close(new_socket);
        return;
    }

    // Serve the requested file
    std::string full_path = "web_files" + file_requested;
    std::cout << "Request for: " << full_path << std::endl;
    serve_file(new_socket, full_path.c_str());
    close(new_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Start a new thread to handle the client
        std::thread client_thread(handle_client, new_socket);
        client_thread.detach();  // Detach the thread so it runs independently
    }

    return 0;
}