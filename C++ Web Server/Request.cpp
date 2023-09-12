#include "Request.h"

http::Request::Request(const std::string& rawRequest) {
	parseRequest(rawRequest);
}

std::string http::Request::getMethod() const {
	return method;
}

std::string http::Request::getPath() const {
	return path;
}

std::string http::Request::getHeader(const std::string& name) const {
	auto it = headers.find(name);

	return (it != headers.end()) ? it->second : "";
}

std::string http::Request::getBody() const {
	return body;
}


std::map<std::string, std::string> http::Request::getAllHeaders() const {
	return headers;
}


void http::Request::parseRequest(const std::string& rawRequest) {
    // Find the request method and path
    std::istringstream requestStream(rawRequest);
    std::string requestLine;
    std::getline(requestStream, requestLine);

    std::istringstream lineStream(requestLine);
    lineStream >> method >> path;

    // Parse headers
    std::string headerLine;
    while (std::getline(requestStream, headerLine) && !headerLine.empty()) {
        size_t colonPos = headerLine.find(':');
        if (colonPos != std::string::npos) {
            std::string headerName = headerLine.substr(0, colonPos);
            std::string headerValue = headerLine.substr(colonPos + 2); // Skip ': ' after header name
            headers[headerName] = headerValue;
        }
    }

    // Parse the request body (if present)
    std::getline(requestStream, body);
}