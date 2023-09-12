#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <string>
#include <functional>
#include <map>
namespace http {
	class Server {
		public:
			Server();

			using RequestHandler = std::function<void(const std::string&, std::string&)>;

			static std::string generateHTTPResponse(const std::string& content);
			// Register a route and its handler
			void registerRoute(const std::string& route, RequestHandler handler);

			void listenToServer(int port);


			void sendResponse(SOCKET socket, const std::string& response);

			~Server();
		private:
			SOCKET wsocket;
			SOCKET new_wsocket;
			WSADATA wsaData;
			struct sockaddr_in server;
			int server_len;
			int BUFFER_SIZE = 30720;
			std::map<std::string, RequestHandler> routeHandlers;
	};
}