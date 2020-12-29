//
//  Socket.cpp
//  HTTP_Server
//

#include "ServerSocket.hpp"

ServerSocket::ServerSocket()
{
    configureSocketAddress(AF_INET, INADDR_ANY, PORT);
}

ServerSocket::ServerSocket(int domain, int addressType, int port)
{
    configureSocketAddress(domain, addressType, port);
}

ServerSocket::ServerSocket(const ServerSocket& socket) : m_socketDescriptor(socket.m_socketDescriptor), m_socketAddress(socket.m_socketAddress), m_socketAddressLength(socket.m_socketAddressLength), m_connectionsCount(socket.m_connectionsCount) { }

ServerSocket::~ServerSocket()
{
    closeSocket();
}

ServerSocket& ServerSocket::operator=(const ServerSocket& socket)
{
    if (this == &socket)
    {
        return *this;
    }
    
    this->m_socketDescriptor = socket.m_socketDescriptor;
    this->m_socketAddress = socket.m_socketAddress;
    this->m_socketAddressLength = socket.m_socketAddressLength;
    this->m_connectionsCount = socket.m_connectionsCount;
    
    return *this;
}

void ServerSocket::configureSocketAddress(int domain, int addressType, int port)
{
    m_socketAddressLength = sizeof(m_socketAddress);
    
    m_socketAddress.sin_family = domain;
    m_socketAddress.sin_addr.s_addr = addressType;
    m_socketAddress.sin_port = htons( port );
    
    memset(m_socketAddress.sin_zero, 0, sizeof(m_socketAddress.sin_zero));
}

bool ServerSocket::createSocket(int domain, int socketType, int protocol)
{
    if ((m_socketDescriptor = socket(domain, socketType, protocol)) == 0)
    {
        perror("Failed to create server socket.");
        
        return false;
    }
    
    return true;
}

bool ServerSocket::bindSocket()
{
    if (bind(m_socketDescriptor, (struct sockaddr *)&m_socketAddress, sizeof(m_socketAddress)) < 0)
    {
        perror("Failed to bind server socket.");
        close(m_socketDescriptor);
        
        return false;
    }
    
    return true;
}

bool ServerSocket::listenSocket(int connectionsCount)
{
    if (listen(m_socketDescriptor, connectionsCount) < 0)
    {
        perror("Error in listen occurred.");
        close(m_socketDescriptor);
        
        return false;
    }
    
    return true;
}

int ServerSocket::acceptConnection()
{
    int clientSocketDescriptor;
    if ((clientSocketDescriptor = accept(m_socketDescriptor, (struct sockaddr *)&m_socketAddress, (socklen_t*)&m_socketAddress)) < 0)
    {
        perror("Failed to accept connection from client socket.");
        close(m_socketDescriptor);
        
        return invalidSocketDescriptorValue;
    }
    
    return clientSocketDescriptor;
}

void ServerSocket::closeSocket()
{
    close(m_socketDescriptor);
}
