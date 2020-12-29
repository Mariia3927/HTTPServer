//
//  HTTPServer.cpp
//  HTTP_Server
//

#include "HTTPServer.hpp"

HTTPServer::HTTPServer() : m_serverSettings(ServerSettings()), m_parser(HTMLParser()), m_responceFactory(HTTPResponceFactory())
{
    configure();
}

HTTPServer::HTTPServer(const ServerSettings& settings): m_serverSettings(settings), m_parser(HTMLParser()), m_responceFactory(HTTPResponceFactory())
{
    configure();
}

HTTPServer::~HTTPServer()
{
    
}

bool HTTPServer::configure()
{
    m_serverSocket = ServerSocket(m_serverSettings.getDomain(), m_serverSettings.getAddressType(), m_serverSettings.getPortNumber());
    
    if (!m_serverSocket.createSocket(m_serverSettings.getDomain(), m_serverSettings.getSocketType(), m_serverSettings.getProtocol()))
    {
        return false;
    }
    
    if (!m_serverSocket.bindSocket())
    {
        return false;
    }
    
    if (!m_serverSocket.listenSocket(m_serverSettings.getAllowedConnectionsCount()))
    {
        return false;
    }
    
    return true;
}

HTTPServer::HTTPServerResponce HTTPServer::serveGETRequest(const ClientSocket& clientSocket)
{
    FileHandler fileHandler(m_parser.getFileName(), m_serverSettings.getServerDirectoryPath() + "/" + m_parser.getFileName());
    
    if (!fileHandler.openFile(m_readBytesMode))
    {
        printf("Failed to find the requested file: %s.", fileHandler.getFilePath().c_str());
        
        return HTTPServerResponce(fileDoesNotExist);
    }
    
    unsigned long fileSize = fileHandler.getFileLength();
    char* buffer = (char*) malloc (sizeof(char)*fileSize);
    size_t bytesRead = fileHandler.read(buffer, fileSize);
    
    if (bytesRead != fileSize)
    {
        printf("Failed to read requested file: %s.", fileHandler.getFilePath().c_str());
        free(buffer);
        
        return HTTPServerResponce(failedToReadFile);
    }
    
    if (!clientSocket.writeHeader(m_responceFactory.makeResponce(fileHandler.getContentType(), m_responceFactory.m_httpOkMessageAndCode, bytesRead)))
    {
        printf("Failed to write header to the socket.");
        free(buffer);
        
        return HTTPServerResponce(failedToWriteToSocket);
    }
    
    if (!clientSocket.sendFileToSocket(buffer, bytesRead))
    {
        printf("Failed to write requested file to the socket.");
        free(buffer);
        
        return HTTPServerResponce(failedToWriteToSocket);
    }
    
    free(buffer);
    
    return HTTPServerResponce(OK);
}

HTTPServer::HTTPServerResponce HTTPServer::servePOSTRequest(const ClientSocket& clientSocket)
{
    FileHandler fileHandler(m_parser.getFileName(), m_serverSettings.getServerDirectoryPath() + "/" + m_parser.getFileName());
    
    if (!fileHandler.openFile(m_writeBytesMode))
    {
        printf("Failed to create file: %s.", fileHandler.getFilePath().c_str());
        
        return HTTPServerResponce(failedToCreateFile);
    }
    
    unsigned long fileSize = m_parser.getContentLength();
    char* buffer = (char*) malloc (sizeof(char)*fileSize);
    memset(buffer, 0, fileSize);
    
    if (!clientSocket.readFromSocket(buffer, fileSize))
    {
        printf("Failed to read file from the socket: %s.", fileHandler.getFilePath().c_str());
        free(buffer);
        
        return HTTPServerResponce(failedToReadFromSocket);
    }
    
    if (!fileHandler.write(buffer, fileSize))
    {
        printf("Failed to write data to the file: %s.", fileHandler.getFilePath().c_str());
        free(buffer);
        
        return HTTPServerResponce(failedToWriteFile);
    }
    
    free(buffer);
    std::string success = "File written successfully.";
    
    if (!clientSocket.writeHeader(m_responceFactory.makeResponce(m_responceFactory.m_contentTypeText, m_responceFactory.m_httpOkMessageAndCode, success.length(), success)))
    {
        printf("Failed to write responce header to the socket.");
    }
    
    return HTTPServerResponce(OK);
}

void HTTPServer::handleErrors(const ClientSocket& clientSocket, const HTTPServerResponce& responceCode)
{
    switch (responceCode)
    {
        case fileDoesNotExist:
            clientSocket.writeHeader(m_responceFactory.makeResponce(m_responceFactory.m_contentTypeText, m_responceFactory.m_httpFileDoesNotExistMessageAndCode, m_responceFactory.m_fileDoesNotExistErrorDescription.length(), m_responceFactory.m_fileDoesNotExistErrorDescription));
            break;
        case failedToCreateFile:
            printf("Failed to create file.");
            break;
        case failedToReadFile:
            printf("Failed to read file.");
            break;
        case failedToWriteFile:
            printf("Failed to write file.");
            break;
        case failedToReadFromSocket:
            printf("Failed to read from socket.");
            break;
        case failedToWriteToSocket:
            printf("Failed to write from socket.");
            break;
        default:
            printf("Operation succeeded.");
            break;
    }
}

void HTTPServer::run()
{
    char* requestHeader = (char*) malloc (m_defaultHeaderBufferLength);
    int m_clientSocketDescriptor;
    
    while(true)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((m_clientSocketDescriptor = m_serverSocket.acceptConnection()) < 0)
        {
            m_serverSocket.closeSocket();
            break;
        }
        
        ClientSocket clientSocket(m_clientSocketDescriptor);
        memset(requestHeader, 0, m_defaultHeaderBufferLength);
        
        if (!clientSocket.readFromSocket(requestHeader, m_defaultHeaderBufferLength))
        {
            m_serverSocket.closeSocket();
            clientSocket.closeSocket();
            break;
        }
        
        m_parser.parseHeader(requestHeader);
        std::string requestType = m_parser.getRequestType();
        HTTPServerResponce result;
        
        if (requestType == m_getRequestDefaultName)
        {
            result = serveGETRequest(clientSocket);
            
            if (result != OK)
            {
                printf("Failed to serve get request.");
                handleErrors(clientSocket, result);
                clientSocket.closeSocket();
                
                if (result != fileDoesNotExist)
                {
                    m_serverSocket.closeSocket();
                    break;
                }
            }
        }
        else if (requestType == m_postRequestDefaultName)
        {
            result = servePOSTRequest(clientSocket);
            
            if (result != OK)
            {
                printf("Failed to serve post request.");
                handleErrors(clientSocket, result);
                m_serverSocket.closeSocket();
                clientSocket.closeSocket();
                
                break;
            }
        }
        else
        {
            printf("Error. Unknown request type. %s", requestType.c_str());
            m_serverSocket.closeSocket();
            clientSocket.closeSocket();
            
            break;
        }
    }
}
