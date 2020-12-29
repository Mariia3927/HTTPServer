//
//  HTTPResponceFactory.cpp
//  HTTP_Server
//

#include "HTTPResponceFactory.hpp"

HTTPResponceFactory::HTTPResponceFactory(): m_httpVersion("HTTP/1.1 ") { }

HTTPResponceFactory::HTTPResponceFactory(const HTTPResponceFactory& header): m_httpVersion(header.m_httpVersion) { }

HTTPResponceFactory& HTTPResponceFactory::operator=(const HTTPResponceFactory& factory)
{
    if (this == &factory)
    {
        return *this;
    }
    
    this->m_httpVersion = factory.m_httpVersion;
    
    return *this;
}

std::string HTTPResponceFactory::makeResponce(const std::string& contentType, const std::string& message, size_t contentLength, const std::string& messageDescription)
{
    std::string responce = m_httpVersion + message + m_contentTypeMessage + contentType + m_contentLengthMessage + std::to_string(int(contentLength)) + m_contentDelimiter + messageDescription;
    
    return responce;
}
