#include "TCP_Server.h"

http::Server::Server() {
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "WSAStartup failed with error: " << WSAGetLastError() << std::endl;
	}
	wsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (wsocket == INVALID_SOCKET) {
		std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
		WSACleanup();
	}
}

std::string http::Server::generateHTTPResponse(const std::string& content) {
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/html\r\n";
    response += "Content-Length: " + std::to_string(content.size()) + "\r\n\r\n";
    response += content;
    return response;
}

void http::Server::listenToServer(int port) {
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;  // Listen on all available network interfaces
	server.sin_port = htons(port);
	server_len = sizeof(server);

	if (bind(wsocket, (SOCKADDR*)&server, server_len) != 0) {
		std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
		closesocket(wsocket);
		WSACleanup();
	}

	if (listen(wsocket, 20) != 0) {
		std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
		closesocket(wsocket);
		WSACleanup();
	}

	std::cout << "Listening on 127.0.0.1:"<<port<<"\n";

    while (true) {
        new_wsocket = accept(wsocket, (SOCKADDR*)&server, &server_len);
        if (new_wsocket == INVALID_SOCKET) {
            std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
            continue;  // Try accepting the next connection
        }

        char buff[30720] = { 0 };
        int bytes = recv(new_wsocket, buff, BUFFER_SIZE, 0);
        std::cout << "Request: " << buff << std::endl;
        if (bytes <= 0) {
            std::cerr << "Receive failed or connection closed." << std::endl;
        }
        else {
            std::string request = buff; // Convert char array to string
            std::string method; // Store the HTTP method (GET, POST, etc.)
            std::string urlPath; // Store the requested URL path

            size_t methodEndPos = request.find(' ');
            if (methodEndPos != std::string::npos) {
                method = request.substr(0, methodEndPos);
                request = request.substr(methodEndPos + 1);
            }

            // Find the second space to identify the URL path
            size_t pathEndPos = request.find(' ');
            if (pathEndPos != std::string::npos) {
                urlPath = request.substr(0, pathEndPos);
            }
            
            auto handlerIter = routeHandlers.find(urlPath);

            if (handlerIter != routeHandlers.end()) {
                // If a matching route handler is found, call it with the request and response data
                std::string response;
                handlerIter->second(request, response);
                sendResponse(new_wsocket, response);
            }
            else {
                // Handle 404 for unknown routes
                std::string response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
                sendResponse(new_wsocket, response);
            }
        }

        closesocket(new_wsocket);
    }
}

void http::Server::sendResponse(SOCKET socket, const std::string& response) {
    int bytesSent = 0;
    int totalBytesSent = 0;
    while (totalBytesSent < response.size()) {
        bytesSent = send(socket, response.c_str() + totalBytesSent, response.size() - totalBytesSent, 0);
        if (bytesSent <= 0) {
            std::cerr << "Send failed." << std::endl;
            break;
        }
        totalBytesSent += bytesSent;
    }
    std::cout << "Sent Response to client" << std::endl;
}




void http::Server::registerRoute(const std::string& route, RequestHandler handler) {
    routeHandlers[route] = handler;
}



http::Server::~Server() {
    closesocket(wsocket);
    WSACleanup();
}