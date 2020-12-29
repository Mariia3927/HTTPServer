//
//  ClientSocket.cpp
//  HTTP_Server
//

#include "ClientSocket.hpp"

ClientSocket::ClientSocket(int descriptor): m_socketDescriptor(descriptor) { }

ClientSocket::ClientSocket(const ClientSocket& socket): m_socketDescriptor(socket.m_socketDescriptor) { }

ClientSocket::~ClientSocket()
{
    closeSocket();
}

ClientSocket& ClientSocket::operator=(const ClientSocket& socket)
{
    if (this == &socket)
    {
        return *this;
    }
    
    this->m_socketDescriptor = socket.m_socketDescriptor;
    
    return *this;
}

bool ClientSocket::readFromSocket(char* buffer, size_t bufferSize) const
{
    size_t bytesCount = read(m_socketDescriptor, buffer, bufferSize);
    
    if(bytesCount <= 0)
    {
        printf("Failed to read from socket.");
        return false;
    }
    
    return true;
}

bool ClientSocket::writeHeader(const std::string& header) const
{
    if (write(m_socketDescriptor, header.c_str(), header.length()) < 0)
    {
        printf("Failed to write header to socket.");
        return false;
    }
   
    return true;
}

bool ClientSocket::sendFileToSocket(char* buffer, size_t bufferSize) const
{
    size_t bytesCount = send(m_socketDescriptor, buffer, bufferSize, 0);
    
    if(bytesCount != bufferSize)
    {
        printf("Failed writing to the socket.");
        return false;
    }

    return true;
}

void ClientSocket::closeSocket()
{
    close(m_socketDescriptor);
}
