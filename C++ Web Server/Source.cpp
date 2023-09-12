#include <iostream>
#include "TCP_Server.h"
#include "Request.h"
#include "Response.h"
int main() {
	using namespace http;

	Server s;

	s.registerRoute("/", [](const std::string& request, std::string& response) {
		std::string content = "<html><h1>Hello Chetan</h1></html>";
		response = Server::generateHTTPResponse(content);
		});

	// Define a route for '/about'
	s.registerRoute("/about", [](const std::string& request, std::string& response) {
		std::string content = "<html><h1>About Us</h1></html>";
		response = Server::generateHTTPResponse(content);
		});

	s.registerRoute("/career", [](const std::string& request, std::string& response) {
		std::string content = "<html><h1>Let's Explore Your Career</h1></html>";
		response = Server::generateHTTPResponse(content);
		});

	s.listenToServer(3000);


	return 0;
}