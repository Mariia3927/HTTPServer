//
//  HTTPResponceFactory.hpp
//  HTTP_Server
//

#ifndef HTTPResponceFactory_hpp
#define HTTPResponceFactory_hpp

#include <stdio.h>
#include <string>

class HTTPResponceFactory
{
private:
    std::string m_httpVersion;
    std::string m_contentTypeMessage = "\r\nContent-Type: ";
    std::string m_contentLengthMessage = "\r\nContent-Length: ";
    std::string m_contentDelimiter = " \r\n\r\n";

public:
    std::string m_contentTypeText = "text/plane";
    std::string m_httpOkMessageAndCode = "200 OK";
    std::string m_httpFileDoesNotExistMessageAndCode = "404 Error";
    std::string m_fileDoesNotExistErrorDescription = "Requested file does not exist.";
    
public:
    HTTPResponceFactory();
    explicit HTTPResponceFactory(const std::string& httpVersion);
    HTTPResponceFactory(const HTTPResponceFactory& header);
    
    HTTPResponceFactory& operator=(const HTTPResponceFactory& factory);
    
    std::string makeResponce(const std::string& contentType, const std::string& messageAndCode, size_t contentLength, const std::string& messageDescription = "");
};

#endif /* HTMLResponceHeader_hpp */
