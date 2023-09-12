#pragma once
#include <string>
#include <map>

namespace http {
    class Response {
    public:
        Response();

        // Set the response status code (e.g., 200 for OK, 404 for Not Found)
        void setStatusCode(int statusCode);

        // Set a response header
        void setHeader(const std::string& name, const std::string& value);

        // Set the response body
        void setBody(const std::string& body);

        // Get the response status code
        int getStatusCode() const;

        // Get a specific response header value by name
        std::string getHeader(const std::string& name) const;

        // Get the response body
        std::string getBody() const;

        // Get all headers as a map
        std::map<std::string, std::string> getAllHeaders() const;

        // Generate the HTTP response string
        std::string generateResponse() const;

    private:
        int statusCode;
        std::map<std::string, std::string> headers;
        std::string body;
    };
}