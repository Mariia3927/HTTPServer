//
//  ClientSocket.hpp
//  HTTP_Server
//

#ifndef ClientSocket_hpp
#define ClientSocket_hpp

#include <sys/socket.h>
#include <unistd.h>
#include <string>

class ClientSocket
{
private:
    int m_socketDescriptor;
    
public:
    ClientSocket() = delete;
    explicit ClientSocket(int descriptor);
    ClientSocket(const ClientSocket&);
    ~ClientSocket();
    
    ClientSocket& operator=(const ClientSocket&);
    
    bool readFromSocket(char* buffer, size_t bufferSize) const;
    bool writeHeader(const std::string& header) const;
    bool sendFileToSocket(char* buffer, size_t bufferSize) const;
    void closeSocket();
};

#endif /* ClientSocket_hpp */
