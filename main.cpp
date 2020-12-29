//
//  main.cpp
//  HTTP_Server
//
//

#include "HTTPServer.hpp"

#define PORT 80
int main(int argc, char const *argv[])
{
    ServerSettings serverSettings = ServerSettings();
    HTTPServer server(serverSettings);
    server.run();
    
    return 0;
}
