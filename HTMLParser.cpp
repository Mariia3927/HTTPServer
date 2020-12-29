//
//  HTMLParser.cpp
//  HTTP_Server
//

#include "HTMLParser.hpp"

HTMLParser::HTMLParser() : m_rawString(""), m_requestType(""), m_filePath(""), m_fileName(""), m_contentLength(0) { }

HTMLParser::HTMLParser(const std:: string& header) : m_rawString(header)
{
    parse();
}

HTMLParser::HTMLParser(const HTMLParser& parser) : m_rawString(parser.m_rawString), m_requestType(parser.m_requestType), m_filePath(parser.m_filePath), m_fileName(parser.m_fileName), m_contentLength(parser.m_contentLength) { }

HTMLParser& HTMLParser::operator=(const HTMLParser& parser)
{
    if (this == &parser)
    {
        return *this;
    }
    
    this->m_rawString = parser.m_rawString;
    this->m_requestType = parser.m_requestType;
    this->m_filePath = parser.m_filePath;
    this->m_fileName = parser.m_fileName;
    this->m_contentLength = parser.m_contentLength;
    
    return *this;
}

void HTMLParser::parse()
{
    size_t firstSpaceIndex = m_rawString.find_first_of(' ');
    if (firstSpaceIndex != std::string::npos)
    {
        m_requestType = m_rawString.substr(0, firstSpaceIndex);
        
        size_t secondSpaceIndex = m_rawString.find(" HTTP/", firstSpaceIndex + 1);
        if (secondSpaceIndex != std::string::npos)
        {
            ++firstSpaceIndex;
            m_filePath = m_rawString.substr(firstSpaceIndex, secondSpaceIndex - firstSpaceIndex);
            
            size_t lastSlashIndex = m_filePath.find_last_of('/');
            if (lastSlashIndex != std::string::npos)
            {
                ++lastSlashIndex;
                m_fileName = m_filePath.substr(lastSlashIndex);
            }
            
            size_t contentLengthStringStartIndex = m_rawString.find(m_defaultContentLengthStringToFind, secondSpaceIndex);
            if (contentLengthStringStartIndex != std::string::npos)
            {
                size_t contentLengthStringValueFirstIndex = contentLengthStringStartIndex + m_defaultContentLengthStringToFind.length();
                
                if (m_rawString[contentLengthStringValueFirstIndex] == ' ')
                {
                    ++contentLengthStringValueFirstIndex;
                }
                
                std::string contentLengthValue = "";
                for(size_t i = contentLengthStringValueFirstIndex; i < m_rawString.length(); i++)
                {
                    if (isdigit(m_rawString[i]))
                    {
                        contentLengthValue += m_rawString[i];
                    }
                    
                    if (m_rawString[i] == ' ')
                    {
                        break;
                    }
                }
                
                m_contentLength = atoi(contentLengthValue.c_str());
            }
        }
    }
}

void HTMLParser::parseHeader(const std::string& header)
{
    m_rawString = header;
    parse();
}

std::string HTMLParser::getRequestType()
{
    return m_requestType;
}

std::string HTMLParser::getFilePath()
{
    return m_filePath;
}

std::string HTMLParser::getFileName()
{
    return m_fileName;
}

int HTMLParser::getContentLength()
{
    return m_contentLength;
}
