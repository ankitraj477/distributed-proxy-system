#include <iostream>
#include <winsock2.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(server_socket, (sockaddr*)&server, sizeof(server));
    listen(server_socket, 3);

    cout << "Proxy listening on port 8080...\n";

    while (true) {
        SOCKET client_socket = accept(server_socket, NULL, NULL);

        char buffer[1024];
       int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
       string request(buffer, bytes_received);

        size_t pos = request.find("Connection: keep-alive");
        if (pos != std::string::npos) {
            request.replace(pos, 22, "Connection: close");
        }


        cout << "Received request\n";
        cout << "Browser request size Backend bytes received: " << bytes_received << "\n";


        // const char* response =
        //     "HTTP/1.1 200 OK\r\n"
        //     "Content-Length: 12\r\n"
        //     "\r\n"
        //     "Hello Proxy";

        // send(client_socket, response, strlen(response), 0);
        // closesocket(client_socket);

            // Create socket to talk to backend
    SOCKET backend_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Backend address structure
    sockaddr_in backend_addr;
    backend_addr.sin_family = AF_INET;
    backend_addr.sin_port = htons(5001);
    backend_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to backend server
    connect(backend_socket, (sockaddr*)&backend_addr, sizeof(backend_addr));

     std::cout << "Connected to backend server\n";

    send(backend_socket, request.c_str(), request.size(), 0);


    char backend_buffer[4096];
    int backend_bytes;
   while ((backend_bytes = recv(backend_socket, backend_buffer, sizeof(backend_buffer), 0)) > 0) {
    send(client_socket, backend_buffer, backend_bytes, 0);
}



    
    
        closesocket(client_socket);
        
    }

    WSACleanup();

    
}
