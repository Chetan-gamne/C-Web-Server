#pragma once
#include <string>
#include <map>
#include <iostream>
#include <sstream>
namespace http {
	class Request {
		public:
            Request(const std::string& rawRequest);

            // Get Request Method
            std::string getMethod() const;

            // Get the requested URL path 
            std::string getPath() const;

            // Get a specific header value by name
            std::string getHeader(const std::string& name) const;

            std::map<std::string, std::string> getAllHeaders() const;
            // Get the request body
            std::string getBody() const;

            // Parse the raw HTTP request string
            void parseRequest(const std::string& rawRequest);


		private:
			std::string method;
			std::string path;
			std::map<std::string, std::string> headers;
			std::string body;
	};
}