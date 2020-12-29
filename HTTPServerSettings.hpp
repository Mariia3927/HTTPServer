//
//  HTTPServerSettings.hpp
//  HTTP_Server
//

#ifndef HTTPServerSettings_hpp
#define HTTPServerSettings_hpp

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <string>

class ServerSettings
{
private:
    int m_domain;
    int m_socketType;
    int m_addressType;
    int m_protocol;
    int m_portNumber;
    std::string m_serverDirectoryPath;
    int m_allowedConnectionsCount;
    
public:
    ServerSettings();
    ServerSettings(int domain, int socketType, int addressType, int protocol, int port, const std::string& dirPath, int connectionsCount);
    ServerSettings(const ServerSettings& settings);
    
    ServerSettings& operator=(const ServerSettings& settings);
    
    int getDomain();
    int getSocketType();
    int getAddressType();
    int getProtocol();
    int getPortNumber();
    std::string getServerDirectoryPath();
    int getAllowedConnectionsCount();
};

#endif /* HTTPServerSettings_hpp */
