#include "Response.h"
#include <sstream>

namespace http {

    Response::Response() : statusCode(200) {}

    void Response::setStatusCode(int code) {
        statusCode = code;
    }

    void Response::setHeader(const std::string& name, const std::string& value) {
        headers[name] = value;
    }

    void Response::setBody(const std::string& responseBody) {
        body = responseBody;
    }

    int Response::getStatusCode() const {
        return statusCode;
    }

    std::string Response::getHeader(const std::string& name) const {
        auto it = headers.find(name);
        return (it != headers.end()) ? it->second : "";
    }

    std::string Response::getBody() const {
        return body;
    }

    std::map<std::string, std::string> Response::getAllHeaders() const {
        return headers;
    }

    std::string Response::generateResponse() const {
        std::ostringstream responseStream;
        responseStream << "HTTP/1.1 " << statusCode << " ";

        // Determine the status phrase based on the status code (you can expand this)
        switch (statusCode) {
        case 200:
            responseStream << "OK";
            break;
        case 404:
            responseStream << "Not Found";
            break;
            // Add more cases as needed
        default:
            responseStream << "Unknown";
        }

        responseStream << "\r\n";

        // Add headers to the response
        for (const auto& header : headers) {
            responseStream << header.first << ": " << header.second << "\r\n";
        }

        // Add a blank line to indicate the end of headers
        responseStream << "\r\n";

        // Add the response body
        responseStream << body;

        return responseStream.str();
    }
}