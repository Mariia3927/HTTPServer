//
//  HTTPServerSettings.cpp
//  HTTP_Server
//

#include "HTTPServerSettings.hpp"

ServerSettings::ServerSettings()
{
    m_domain = AF_INET;
    m_socketType = SOCK_STREAM;
    m_addressType = INADDR_ANY;
    m_protocol = 0;
    m_portNumber = 80;
    m_allowedConnectionsCount = 10;
    char buffer[256];
    getcwd(buffer, 256);
    m_serverDirectoryPath = buffer;
};

ServerSettings::ServerSettings(int domain, int socketType, int addressType, int protocol, int port, const std::string& dirPath, int connectionsCount) : m_domain(domain), m_socketType(socketType), m_addressType(addressType), m_protocol(protocol), m_portNumber(port), m_serverDirectoryPath(dirPath), m_allowedConnectionsCount(connectionsCount) { };

ServerSettings::ServerSettings(const ServerSettings& settings) : m_domain(settings.m_domain), m_socketType(settings.m_socketType), m_addressType(settings.m_addressType), m_protocol(settings.m_protocol), m_portNumber(settings.m_portNumber), m_serverDirectoryPath(settings.m_serverDirectoryPath), m_allowedConnectionsCount(settings.m_allowedConnectionsCount) { };

ServerSettings& ServerSettings::operator=(const ServerSettings& settings)
{
    if (this == &settings)
    {
        return *this;
    }
    
    this->m_domain = settings.m_domain;
    this->m_socketType = settings.m_socketType;
    this->m_addressType = settings.m_addressType;
    this->m_protocol = settings.m_protocol;
    this->m_portNumber = settings.m_portNumber;
    this->m_serverDirectoryPath = settings.m_serverDirectoryPath;
    this->m_allowedConnectionsCount = settings.m_allowedConnectionsCount;
    
    return *this;
}

int ServerSettings::getDomain()
{
    return m_domain;
}

int ServerSettings::getSocketType()
{
    return m_socketType;
}

int ServerSettings::getAddressType()
{
    return m_addressType;
}

int ServerSettings::getProtocol()
{
    return m_protocol;
}

int ServerSettings::getPortNumber()
{
    return m_portNumber;
}

std::string ServerSettings::getServerDirectoryPath()
{
    return m_serverDirectoryPath;
}

int ServerSettings::getAllowedConnectionsCount()
{
    return m_allowedConnectionsCount;
}
