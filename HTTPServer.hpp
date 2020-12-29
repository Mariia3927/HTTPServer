//
//  HTTPServer.hpp
//  HTTP_Server
//

#ifndef HTTPServer_hpp
#define HTTPServer_hpp

#include "HTTPServerSettings.hpp"
#include "FileHandler.hpp"
#include "ServerSocket.hpp"
#include "ClientSocket.hpp"
#include "HTMLParser.hpp"
#include "HTTPResponceFactory.hpp"

class HTTPServer
{
private:
    ServerSettings m_serverSettings;
    HTMLParser m_parser;
    ServerSocket m_serverSocket;
    HTTPResponceFactory m_responceFactory;
    size_t m_defaultHeaderBufferLength = 256;
    std::string m_getRequestDefaultName = "GET";
    std::string m_postRequestDefaultName = "POST";
    std::string m_readBytesMode = "rb";
    std::string m_writeBytesMode = "wb";
    
    enum HTTPServerResponce { OK = 0, fileDoesNotExist, failedToCreateFile, failedToReadFile, failedToWriteFile, failedToReadFromSocket, failedToWriteToSocket };
    
private:
    bool configure();
    HTTPServerResponce serveGETRequest(const ClientSocket& clientSocket);
    HTTPServerResponce servePOSTRequest(const ClientSocket& clientSocket);
    void handleErrors(const ClientSocket& clientSocket, const HTTPServerResponce& responceCode);
    
public:
    HTTPServer();
    explicit HTTPServer(const ServerSettings& settings);
    HTTPServer(const HTTPServer&) = delete;
    ~HTTPServer();
    
    HTTPServer& operator=(const HTTPServer& server) = delete;
    
    void run();
};

#endif /* HTTPServer_hpp */
