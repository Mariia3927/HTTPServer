//
//  HTMLParser.hpp
//  HTTP_Server
//

#ifndef HTMLParser_hpp
#define HTMLParser_hpp

#include <string>

class HTMLParser
{
private:
    std::string m_rawString;
    std::string m_requestType;
    std::string m_filePath;
    std::string m_fileName;
    int m_contentLength;
    std::string m_defaultContentLengthStringToFind = "Content-Length:";
    
    void parse();
public:
    HTMLParser();
    explicit HTMLParser(const std::string& header);
    HTMLParser(const HTMLParser&);
    
    HTMLParser& operator=(const HTMLParser&);
    
    void parseHeader(const std::string& header);
    std::string getRequestType();
    std::string getFilePath();
    std::string getFileName();
    int getContentLength();
};

#endif /* HTMLParser_hpp */
