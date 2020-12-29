//
//  FileHandler.cpp
//  HTTP_Server
//

#include "FileHandler.hpp"

FileHandler::FileHandler() { }

FileHandler::FileHandler(const std::string& name, const std::string& path) : m_fileName(name), m_filePath(path)
{
    parseFileName();
}

FileHandler::~FileHandler()
{
    closeFile();
}

void FileHandler::parseFileName()
{
    size_t dotIndex = m_fileName.find_last_of('.');
    
    if (dotIndex != std::string::npos)
    {
        ++dotIndex;
        m_fileExtension = m_fileName.substr(dotIndex);
    }
}

std::string FileHandler::getFileName()
{
    return m_fileName;
}

std::string FileHandler::getFilePath()
{
    return m_filePath;
}

unsigned long FileHandler::getFileLength()
{
    fseek (m_fileDescriptor, 0, SEEK_END);
    long fileSize = ftell(m_fileDescriptor);
    rewind(m_fileDescriptor);
    
    return fileSize;
}

std::string FileHandler::getContentType()
{
    if (m_fileExtension != "")
    {
        std::string lowercasedFileExtension = m_fileExtension;
        std::transform(lowercasedFileExtension.begin(), lowercasedFileExtension.end(), lowercasedFileExtension.begin(), ::tolower);
        
        if (lowercasedFileExtension == "jpg" || lowercasedFileExtension == "jpeg")
        {
            return m_contentTypes[JpegImage];
        }
        else if (lowercasedFileExtension == "gif")
        {
            return m_contentTypes[GifImage];
        }
        else if (lowercasedFileExtension == "bmp")
        {
            return m_contentTypes[BmpImage];
        }
        else if (lowercasedFileExtension == "tiff")
        {
            return m_contentTypes[TiffImage];
        }
        else if (lowercasedFileExtension == "png")
        {
            return m_contentTypes[PngImage];
        }
        else if (lowercasedFileExtension == "txt")
        {
            return m_contentTypes[TextDocument];
        }
    }
    
    return m_contentTypes[AnyKindOfBinary];
}

bool FileHandler::openFile(const std::string& mode)
{
    m_fileDescriptor = fopen(m_filePath.c_str(), mode.c_str());
    return m_fileDescriptor != NULL;
}

bool FileHandler::write(void* buffer, size_t length)
{
    if (fwrite(buffer, 1, length, m_fileDescriptor) > 0)
    {
        return true;
    }
    else
    {
        printf("Failed to write data.");
        return false;
    }
}

size_t FileHandler::read(void* buffer, size_t length)
{
    size_t bytesRead = fread(buffer, 1, length, m_fileDescriptor);
    if (bytesRead > 0)
    {
        return bytesRead;
    }
    else
    {
        printf("Failed to read file.");
        return 0;
    }
}

void FileHandler::closeFile()
{
    fclose(m_fileDescriptor);
}
