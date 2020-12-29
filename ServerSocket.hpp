//
//  Socket.hpp
//  HTTP_Server
//

#ifndef Socket_hpp
#define Socket_hpp

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <filesystem>

#define PORT 80
class ServerSocket
{
private:
    int m_socketDescriptor;
    sockaddr_in m_socketAddress;
    int m_socketAddressLength;
    int m_connectionsCount;
    int invalidSocketDescriptorValue = -1;
    
private:
    void configureSocketAddress(int domain, int addressType, int port);
    
public:
    ServerSocket();
    ServerSocket(int domain, int addressType, int port);
    ServerSocket(const ServerSocket&);
    ~ServerSocket();
    
    ServerSocket& operator=(const ServerSocket&);
    bool createSocket(int domain, int socketType, int protocol);
    bool bindSocket();
    bool listenSocket(int connectionsCount);
    int acceptConnection();
    void closeSocket();
};

#endif /* Socket_hpp */
